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
typedef  scalar_t__ u32 ;
struct xfrm_state {struct xfrm_sec_ctx* security; } ;
struct xfrm_sec_ctx {int ctx_len; int /*<<< orphan*/  ctx_str; scalar_t__ ctx_sid; int /*<<< orphan*/  ctx_alg; int /*<<< orphan*/  ctx_doi; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  XFRM_SC_ALG_SELINUX ; 
 int /*<<< orphan*/  XFRM_SC_DOI_LSM ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 struct xfrm_sec_ctx* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int security_sid_to_context (int /*<<< orphan*/ *,scalar_t__,char**,int*) ; 
 int /*<<< orphan*/  selinux_state ; 
 int /*<<< orphan*/  selinux_xfrm_refcount ; 

int selinux_xfrm_state_alloc_acquire(struct xfrm_state *x,
				     struct xfrm_sec_ctx *polsec, u32 secid)
{
	int rc;
	struct xfrm_sec_ctx *ctx;
	char *ctx_str = NULL;
	int str_len;

	if (!polsec)
		return 0;

	if (secid == 0)
		return -EINVAL;

	rc = security_sid_to_context(&selinux_state, secid, &ctx_str,
				     &str_len);
	if (rc)
		return rc;

	ctx = kmalloc(sizeof(*ctx) + str_len, GFP_ATOMIC);
	if (!ctx) {
		rc = -ENOMEM;
		goto out;
	}

	ctx->ctx_doi = XFRM_SC_DOI_LSM;
	ctx->ctx_alg = XFRM_SC_ALG_SELINUX;
	ctx->ctx_sid = secid;
	ctx->ctx_len = str_len;
	memcpy(ctx->ctx_str, ctx_str, str_len);

	x->security = ctx;
	atomic_inc(&selinux_xfrm_refcount);
out:
	kfree(ctx_str);
	return rc;
}