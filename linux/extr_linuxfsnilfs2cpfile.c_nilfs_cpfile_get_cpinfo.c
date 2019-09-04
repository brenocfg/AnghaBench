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
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
#define  NILFS_CHECKPOINT 129 
#define  NILFS_SNAPSHOT 128 
 int /*<<< orphan*/  nilfs_cpfile_do_get_cpinfo (struct inode*,int /*<<< orphan*/ *,void*,unsigned int,size_t) ; 
 int /*<<< orphan*/  nilfs_cpfile_do_get_ssinfo (struct inode*,int /*<<< orphan*/ *,void*,unsigned int,size_t) ; 

ssize_t nilfs_cpfile_get_cpinfo(struct inode *cpfile, __u64 *cnop, int mode,
				void *buf, unsigned int cisz, size_t nci)
{
	switch (mode) {
	case NILFS_CHECKPOINT:
		return nilfs_cpfile_do_get_cpinfo(cpfile, cnop, buf, cisz, nci);
	case NILFS_SNAPSHOT:
		return nilfs_cpfile_do_get_ssinfo(cpfile, cnop, buf, cisz, nci);
	default:
		return -EINVAL;
	}
}