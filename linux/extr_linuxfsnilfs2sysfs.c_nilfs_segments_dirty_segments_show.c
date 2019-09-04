#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct the_nilfs {int /*<<< orphan*/  ns_sb; int /*<<< orphan*/  ns_segctor_sem; int /*<<< orphan*/  ns_sufile; } ;
struct nilfs_sustat {int /*<<< orphan*/  ss_ndirtysegs; } ;
struct nilfs_segments_attr {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nilfs_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int nilfs_sufile_get_stat (int /*<<< orphan*/ ,struct nilfs_sustat*) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
nilfs_segments_dirty_segments_show(struct nilfs_segments_attr *attr,
				    struct the_nilfs *nilfs,
				    char *buf)
{
	struct nilfs_sustat sustat;
	int err;

	down_read(&nilfs->ns_segctor_sem);
	err = nilfs_sufile_get_stat(nilfs->ns_sufile, &sustat);
	up_read(&nilfs->ns_segctor_sem);
	if (err < 0) {
		nilfs_msg(nilfs->ns_sb, KERN_ERR,
			  "unable to get segment stat: err=%d", err);
		return err;
	}

	return snprintf(buf, PAGE_SIZE, "%llu\n", sustat.ss_ndirtysegs);
}