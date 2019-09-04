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
struct xfrm_user_sec_ctx {int len; int ctx_len; int /*<<< orphan*/  ctx_alg; int /*<<< orphan*/  ctx_doi; int /*<<< orphan*/  exttype; } ;
struct xfrm_sec_ctx {int ctx_len; int /*<<< orphan*/  ctx_str; int /*<<< orphan*/  ctx_alg; int /*<<< orphan*/  ctx_doi; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  XFRMA_SEC_CTX ; 
 int /*<<< orphan*/  memcpy (struct xfrm_user_sec_ctx*,int /*<<< orphan*/ ,int) ; 
 struct xfrm_user_sec_ctx* nla_data (struct nlattr*) ; 
 struct nlattr* nla_reserve (struct sk_buff*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int copy_sec_ctx(struct xfrm_sec_ctx *s, struct sk_buff *skb)
{
	struct xfrm_user_sec_ctx *uctx;
	struct nlattr *attr;
	int ctx_size = sizeof(*uctx) + s->ctx_len;

	attr = nla_reserve(skb, XFRMA_SEC_CTX, ctx_size);
	if (attr == NULL)
		return -EMSGSIZE;

	uctx = nla_data(attr);
	uctx->exttype = XFRMA_SEC_CTX;
	uctx->len = ctx_size;
	uctx->ctx_doi = s->ctx_doi;
	uctx->ctx_alg = s->ctx_alg;
	uctx->ctx_len = s->ctx_len;
	memcpy(uctx + 1, s->ctx_str, s->ctx_len);

	return 0;
}