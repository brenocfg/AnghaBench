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
struct ceph_acl_sec_ctx {scalar_t__ pagelist; int /*<<< orphan*/  sec_ctxlen; int /*<<< orphan*/  sec_ctx; int /*<<< orphan*/  default_acl; int /*<<< orphan*/  acl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_pagelist_release (scalar_t__) ; 
 int /*<<< orphan*/  posix_acl_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  security_release_secctx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ceph_release_acl_sec_ctx(struct ceph_acl_sec_ctx *as_ctx)
{
#ifdef CONFIG_CEPH_FS_POSIX_ACL
	posix_acl_release(as_ctx->acl);
	posix_acl_release(as_ctx->default_acl);
#endif
#ifdef CONFIG_CEPH_FS_SECURITY_LABEL
	security_release_secctx(as_ctx->sec_ctx, as_ctx->sec_ctxlen);
#endif
	if (as_ctx->pagelist)
		ceph_pagelist_release(as_ctx->pagelist);
}