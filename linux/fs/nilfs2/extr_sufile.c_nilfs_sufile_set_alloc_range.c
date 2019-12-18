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
struct nilfs_sufile_info {scalar_t__ allocmax; scalar_t__ allocmin; } ;
struct inode {int dummy; } ;
typedef  scalar_t__ __u64 ;
struct TYPE_2__ {int /*<<< orphan*/  mi_sem; } ;

/* Variables and functions */
 int ERANGE ; 
 TYPE_1__* NILFS_MDT (struct inode*) ; 
 struct nilfs_sufile_info* NILFS_SUI (struct inode*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 scalar_t__ nilfs_sufile_get_nsegments (struct inode*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int nilfs_sufile_set_alloc_range(struct inode *sufile, __u64 start, __u64 end)
{
	struct nilfs_sufile_info *sui = NILFS_SUI(sufile);
	__u64 nsegs;
	int ret = -ERANGE;

	down_write(&NILFS_MDT(sufile)->mi_sem);
	nsegs = nilfs_sufile_get_nsegments(sufile);

	if (start <= end && end < nsegs) {
		sui->allocmin = start;
		sui->allocmax = end;
		ret = 0;
	}
	up_write(&NILFS_MDT(sufile)->mi_sem);
	return ret;
}