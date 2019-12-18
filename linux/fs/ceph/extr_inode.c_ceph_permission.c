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
 int /*<<< orphan*/  CEPH_CAP_AUTH_SHARED ; 
 int ECHILD ; 
 int MAY_NOT_BLOCK ; 
 int ceph_do_getattr (struct inode*,int /*<<< orphan*/ ,int) ; 
 int generic_permission (struct inode*,int) ; 

int ceph_permission(struct inode *inode, int mask)
{
	int err;

	if (mask & MAY_NOT_BLOCK)
		return -ECHILD;

	err = ceph_do_getattr(inode, CEPH_CAP_AUTH_SHARED, false);

	if (!err)
		err = generic_permission(inode, mask);
	return err;
}