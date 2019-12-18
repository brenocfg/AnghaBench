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
typedef  int u32 ;
struct xfrm_user_sec_ctx {scalar_t__ ctx_doi; scalar_t__ ctx_alg; int ctx_len; } ;
struct xfrm_sec_ctx {int ctx_len; char* ctx_str; int /*<<< orphan*/  ctx_sid; scalar_t__ ctx_alg; scalar_t__ ctx_doi; } ;
struct task_security_struct {int /*<<< orphan*/  sid; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSOCIATION__SETCONTEXT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  SECCLASS_ASSOCIATION ; 
 scalar_t__ XFRM_SC_ALG_SELINUX ; 
 scalar_t__ XFRM_SC_DOI_LSM ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int avc_has_perm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current_cred () ; 
 int /*<<< orphan*/  kfree (struct xfrm_sec_ctx*) ; 
 struct xfrm_sec_ctx* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,struct xfrm_user_sec_ctx*,int) ; 
 int security_context_to_sid (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct task_security_struct* selinux_cred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selinux_state ; 
 int /*<<< orphan*/  selinux_xfrm_refcount ; 

__attribute__((used)) static int selinux_xfrm_alloc_user(struct xfrm_sec_ctx **ctxp,
				   struct xfrm_user_sec_ctx *uctx,
				   gfp_t gfp)
{
	int rc;
	const struct task_security_struct *tsec = selinux_cred(current_cred());
	struct xfrm_sec_ctx *ctx = NULL;
	u32 str_len;

	if (ctxp == NULL || uctx == NULL ||
	    uctx->ctx_doi != XFRM_SC_DOI_LSM ||
	    uctx->ctx_alg != XFRM_SC_ALG_SELINUX)
		return -EINVAL;

	str_len = uctx->ctx_len;
	if (str_len >= PAGE_SIZE)
		return -ENOMEM;

	ctx = kmalloc(sizeof(*ctx) + str_len + 1, gfp);
	if (!ctx)
		return -ENOMEM;

	ctx->ctx_doi = XFRM_SC_DOI_LSM;
	ctx->ctx_alg = XFRM_SC_ALG_SELINUX;
	ctx->ctx_len = str_len;
	memcpy(ctx->ctx_str, &uctx[1], str_len);
	ctx->ctx_str[str_len] = '\0';
	rc = security_context_to_sid(&selinux_state, ctx->ctx_str, str_len,
				     &ctx->ctx_sid, gfp);
	if (rc)
		goto err;

	rc = avc_has_perm(&selinux_state,
			  tsec->sid, ctx->ctx_sid,
			  SECCLASS_ASSOCIATION, ASSOCIATION__SETCONTEXT, NULL);
	if (rc)
		goto err;

	*ctxp = ctx;
	atomic_inc(&selinux_xfrm_refcount);
	return 0;

err:
	kfree(ctx);
	return rc;
}