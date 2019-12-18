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
struct xfrm_sec_ctx {scalar_t__ ctx_len; } ;
struct xfrm_policy {struct xfrm_sec_ctx* security; } ;
struct sadb_x_sec_ctx {int dummy; } ;

/* Variables and functions */
 int PFKEY_ALIGN8 (int) ; 

__attribute__((used)) static inline int pfkey_xfrm_policy2sec_ctx_size(const struct xfrm_policy *xp)
{
	struct xfrm_sec_ctx *xfrm_ctx = xp->security;

	if (xfrm_ctx) {
		int len = sizeof(struct sadb_x_sec_ctx);
		len += xfrm_ctx->ctx_len;
		return PFKEY_ALIGN8(len);
	}
	return 0;
}