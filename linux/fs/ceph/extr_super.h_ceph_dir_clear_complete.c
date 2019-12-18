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
 int /*<<< orphan*/  __ceph_dir_clear_complete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_inode (struct inode*) ; 

__attribute__((used)) static inline void ceph_dir_clear_complete(struct inode *inode)
{
	__ceph_dir_clear_complete(ceph_inode(inode));
}