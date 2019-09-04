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
struct inode {int dummy; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {scalar_t__ i_reported_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUOTA_CHECK_MAX_BYTES_APPROACHING_OP ; 
 int /*<<< orphan*/  ceph_has_realms_with_quotas (struct inode*) ; 
 TYPE_1__* ceph_inode (struct inode*) ; 
 int check_quota_exceeded (struct inode*,int /*<<< orphan*/ ,scalar_t__) ; 

bool ceph_quota_is_max_bytes_approaching(struct inode *inode, loff_t newsize)
{
	loff_t size = ceph_inode(inode)->i_reported_size;

	if (!ceph_has_realms_with_quotas(inode))
		return false;

	/* return immediately if we're decreasing file size */
	if (newsize <= size)
		return false;

	return check_quota_exceeded(inode, QUOTA_CHECK_MAX_BYTES_APPROACHING_OP,
				    (newsize - size));
}