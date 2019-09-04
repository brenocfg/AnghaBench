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

/* Variables and functions */
 int __ceph_dir_is_complete_ordered (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_inode (struct inode*) ; 
 int /*<<< orphan*/  smp_rmb () ; 

__attribute__((used)) static inline bool ceph_dir_is_complete_ordered(struct inode *inode)
{
	bool ret = __ceph_dir_is_complete_ordered(ceph_inode(inode));
	smp_rmb();
	return ret;
}