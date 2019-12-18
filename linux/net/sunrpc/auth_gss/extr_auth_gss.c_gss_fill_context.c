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
typedef  int /*<<< orphan*/  window_size ;
typedef  unsigned int u32 ;
typedef  int /*<<< orphan*/  timeout ;
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct gss_cl_ctx {unsigned long gc_expiry; unsigned int gc_win; TYPE_1__ gc_acceptor; int /*<<< orphan*/  gc_gss_ctx; TYPE_1__ gc_wire_ctx; } ;
struct gss_api_mech {int dummy; } ;
typedef  int /*<<< orphan*/  seclen ;
typedef  int /*<<< orphan*/  ret ;

/* Variables and functions */
 int EACCES ; 
 int EFAULT ; 
 int EKEYEXPIRED ; 
 void* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 unsigned int GSSD_MIN_TIMEOUT ; 
 unsigned long HZ ; 
 scalar_t__ IS_ERR (void const*) ; 
 int gss_import_sec_context (void const*,unsigned int,struct gss_api_mech*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 void* simple_get_bytes (void const*,void const*,...) ; 
 void* simple_get_netobj (void const*,void const*,TYPE_1__*) ; 
 int /*<<< orphan*/  trace_rpcgss_context (unsigned long,unsigned long,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_rpcgss_import_ctx (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static const void *
gss_fill_context(const void *p, const void *end, struct gss_cl_ctx *ctx, struct gss_api_mech *gm)
{
	const void *q;
	unsigned int seclen;
	unsigned int timeout;
	unsigned long now = jiffies;
	u32 window_size;
	int ret;

	/* First unsigned int gives the remaining lifetime in seconds of the
	 * credential - e.g. the remaining TGT lifetime for Kerberos or
	 * the -t value passed to GSSD.
	 */
	p = simple_get_bytes(p, end, &timeout, sizeof(timeout));
	if (IS_ERR(p))
		goto err;
	if (timeout == 0)
		timeout = GSSD_MIN_TIMEOUT;
	ctx->gc_expiry = now + ((unsigned long)timeout * HZ);
	/* Sequence number window. Determines the maximum number of
	 * simultaneous requests
	 */
	p = simple_get_bytes(p, end, &window_size, sizeof(window_size));
	if (IS_ERR(p))
		goto err;
	ctx->gc_win = window_size;
	/* gssd signals an error by passing ctx->gc_win = 0: */
	if (ctx->gc_win == 0) {
		/*
		 * in which case, p points to an error code. Anything other
		 * than -EKEYEXPIRED gets converted to -EACCES.
		 */
		p = simple_get_bytes(p, end, &ret, sizeof(ret));
		if (!IS_ERR(p))
			p = (ret == -EKEYEXPIRED) ? ERR_PTR(-EKEYEXPIRED) :
						    ERR_PTR(-EACCES);
		goto err;
	}
	/* copy the opaque wire context */
	p = simple_get_netobj(p, end, &ctx->gc_wire_ctx);
	if (IS_ERR(p))
		goto err;
	/* import the opaque security context */
	p  = simple_get_bytes(p, end, &seclen, sizeof(seclen));
	if (IS_ERR(p))
		goto err;
	q = (const void *)((const char *)p + seclen);
	if (unlikely(q > end || q < p)) {
		p = ERR_PTR(-EFAULT);
		goto err;
	}
	ret = gss_import_sec_context(p, seclen, gm, &ctx->gc_gss_ctx, NULL, GFP_NOFS);
	if (ret < 0) {
		trace_rpcgss_import_ctx(ret);
		p = ERR_PTR(ret);
		goto err;
	}

	/* is there any trailing data? */
	if (q == end) {
		p = q;
		goto done;
	}

	/* pull in acceptor name (if there is one) */
	p = simple_get_netobj(q, end, &ctx->gc_acceptor);
	if (IS_ERR(p))
		goto err;
done:
	trace_rpcgss_context(ctx->gc_expiry, now, timeout,
			     ctx->gc_acceptor.len, ctx->gc_acceptor.data);
err:
	return p;
}