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
struct nilfs_cpinfo {scalar_t__ ci_cno; } ;
struct inode {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  ci ;
typedef  scalar_t__ __u64 ;

/* Variables and functions */
 int EBUSY ; 
 int ENOENT ; 
 int nilfs_cpfile_delete_checkpoints (struct inode*,scalar_t__,scalar_t__) ; 
 scalar_t__ nilfs_cpfile_do_get_cpinfo (struct inode*,scalar_t__*,struct nilfs_cpinfo*,int,int) ; 
 scalar_t__ nilfs_cpinfo_snapshot (struct nilfs_cpinfo*) ; 

int nilfs_cpfile_delete_checkpoint(struct inode *cpfile, __u64 cno)
{
	struct nilfs_cpinfo ci;
	__u64 tcno = cno;
	ssize_t nci;

	nci = nilfs_cpfile_do_get_cpinfo(cpfile, &tcno, &ci, sizeof(ci), 1);
	if (nci < 0)
		return nci;
	else if (nci == 0 || ci.ci_cno != cno)
		return -ENOENT;
	else if (nilfs_cpinfo_snapshot(&ci))
		return -EBUSY;

	return nilfs_cpfile_delete_checkpoints(cpfile, cno, cno + 1);
}