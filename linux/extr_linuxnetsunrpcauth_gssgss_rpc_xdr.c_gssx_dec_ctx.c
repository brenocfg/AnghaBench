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
struct xdr_stream {int dummy; } ;
struct gssx_ctx {int /*<<< orphan*/  options; int /*<<< orphan*/  open; int /*<<< orphan*/  locally_initiated; int /*<<< orphan*/  ctx_flags; int /*<<< orphan*/  lifetime; int /*<<< orphan*/  targ_name; int /*<<< orphan*/  src_name; int /*<<< orphan*/  mech; int /*<<< orphan*/  need_release; int /*<<< orphan*/  state; int /*<<< orphan*/  exported_context_token; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENOSPC ; 
 int dummy_dec_opt_array (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int gssx_dec_bool (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int gssx_dec_buffer (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int gssx_dec_name (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_decode_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_inline_decode (struct xdr_stream*,int) ; 

__attribute__((used)) static int gssx_dec_ctx(struct xdr_stream *xdr,
			struct gssx_ctx *ctx)
{
	__be32 *p;
	int err;

	/* ctx->exported_context_token */
	err = gssx_dec_buffer(xdr, &ctx->exported_context_token);
	if (err)
		return err;

	/* ctx->state */
	err = gssx_dec_buffer(xdr, &ctx->state);
	if (err)
		return err;

	/* ctx->need_release */
	err = gssx_dec_bool(xdr, &ctx->need_release);
	if (err)
		return err;

	/* ctx->mech */
	err = gssx_dec_buffer(xdr, &ctx->mech);
	if (err)
		return err;

	/* ctx->src_name */
	err = gssx_dec_name(xdr, &ctx->src_name);
	if (err)
		return err;

	/* ctx->targ_name */
	err = gssx_dec_name(xdr, &ctx->targ_name);
	if (err)
		return err;

	/* ctx->lifetime */
	p = xdr_inline_decode(xdr, 8+8);
	if (unlikely(p == NULL))
		return -ENOSPC;
	p = xdr_decode_hyper(p, &ctx->lifetime);

	/* ctx->ctx_flags */
	p = xdr_decode_hyper(p, &ctx->ctx_flags);

	/* ctx->locally_initiated */
	err = gssx_dec_bool(xdr, &ctx->locally_initiated);
	if (err)
		return err;

	/* ctx->open */
	err = gssx_dec_bool(xdr, &ctx->open);
	if (err)
		return err;

	/* we assume we have no options for now, so simply consume them */
	/* ctx->options */
	err = dummy_dec_opt_array(xdr, &ctx->options);

	return err;
}