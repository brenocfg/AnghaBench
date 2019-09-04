#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct the_nilfs {int /*<<< orphan*/  ns_dat; int /*<<< orphan*/  ns_sufile; } ;
struct nilfs_segments_attr {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  mi_sem; } ;

/* Variables and functions */
 TYPE_1__* NILFS_MDT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 unsigned long nilfs_sufile_get_ncleansegs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,unsigned long) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
nilfs_segments_clean_segments_show(struct nilfs_segments_attr *attr,
				    struct the_nilfs *nilfs,
				    char *buf)
{
	unsigned long ncleansegs;

	down_read(&NILFS_MDT(nilfs->ns_dat)->mi_sem);
	ncleansegs = nilfs_sufile_get_ncleansegs(nilfs->ns_sufile);
	up_read(&NILFS_MDT(nilfs->ns_dat)->mi_sem);

	return snprintf(buf, PAGE_SIZE, "%lu\n", ncleansegs);
}