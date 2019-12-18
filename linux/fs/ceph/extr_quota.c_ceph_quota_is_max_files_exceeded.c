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
struct inode {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUOTA_CHECK_MAX_FILES_OP ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ceph_has_realms_with_quotas (struct inode*) ; 
 int check_quota_exceeded (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool ceph_quota_is_max_files_exceeded(struct inode *inode)
{
	if (!ceph_has_realms_with_quotas(inode))
		return false;

	WARN_ON(!S_ISDIR(inode->i_mode));

	return check_quota_exceeded(inode, QUOTA_CHECK_MAX_FILES_OP, 0);
}