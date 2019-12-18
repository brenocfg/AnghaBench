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
struct ceph_acl_sec_ctx {int /*<<< orphan*/  default_acl; int /*<<< orphan*/  acl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_TYPE_ACCESS ; 
 int /*<<< orphan*/  ACL_TYPE_DEFAULT ; 
 int /*<<< orphan*/  ceph_set_cached_acl (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ceph_init_inode_acls(struct inode *inode, struct ceph_acl_sec_ctx *as_ctx)
{
	if (!inode)
		return;
	ceph_set_cached_acl(inode, ACL_TYPE_ACCESS, as_ctx->acl);
	ceph_set_cached_acl(inode, ACL_TYPE_DEFAULT, as_ctx->default_acl);
}