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
 int __ceph_do_getattr (struct inode*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static inline int ceph_do_getattr(struct inode *inode, int mask, bool force)
{
	return __ceph_do_getattr(inode, NULL, mask, force);
}