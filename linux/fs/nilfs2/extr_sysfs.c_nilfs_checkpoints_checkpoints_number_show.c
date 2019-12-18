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
struct the_nilfs {int /*<<< orphan*/  ns_sb; int /*<<< orphan*/  ns_segctor_sem; int /*<<< orphan*/  ns_cpfile; } ;
struct nilfs_cpstat {int /*<<< orphan*/  cs_ncps; } ;
struct nilfs_checkpoints_attr {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int nilfs_cpfile_get_stat (int /*<<< orphan*/ ,struct nilfs_cpstat*) ; 
 int /*<<< orphan*/  nilfs_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
nilfs_checkpoints_checkpoints_number_show(struct nilfs_checkpoints_attr *attr,
					    struct the_nilfs *nilfs,
					    char *buf)
{
	__u64 ncheckpoints;
	struct nilfs_cpstat cpstat;
	int err;

	down_read(&nilfs->ns_segctor_sem);
	err = nilfs_cpfile_get_stat(nilfs->ns_cpfile, &cpstat);
	up_read(&nilfs->ns_segctor_sem);
	if (err < 0) {
		nilfs_msg(nilfs->ns_sb, KERN_ERR,
			  "unable to get checkpoint stat: err=%d", err);
		return err;
	}

	ncheckpoints = cpstat.cs_ncps;

	return snprintf(buf, PAGE_SIZE, "%llu\n", ncheckpoints);
}