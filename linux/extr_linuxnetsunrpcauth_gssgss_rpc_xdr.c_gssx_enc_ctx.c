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
 int dummy_enc_opt_array (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int gssx_enc_bool (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 int gssx_enc_buffer (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int gssx_enc_name (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_encode_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,int) ; 

__attribute__((used)) static int gssx_enc_ctx(struct xdr_stream *xdr,
			struct gssx_ctx *ctx)
{
	__be32 *p;
	int err;

	/* ctx->exported_context_token */
	err = gssx_enc_buffer(xdr, &ctx->exported_context_token);
	if (err)
		return err;

	/* ctx->state */
	err = gssx_enc_buffer(xdr, &ctx->state);
	if (err)
		return err;

	/* ctx->need_release */
	err = gssx_enc_bool(xdr, ctx->need_release);
	if (err)
		return err;

	/* ctx->mech */
	err = gssx_enc_buffer(xdr, &ctx->mech);
	if (err)
		return err;

	/* ctx->src_name */
	err = gssx_enc_name(xdr, &ctx->src_name);
	if (err)
		return err;

	/* ctx->targ_name */
	err = gssx_enc_name(xdr, &ctx->targ_name);
	if (err)
		return err;

	/* ctx->lifetime */
	p = xdr_reserve_space(xdr, 8+8);
	if (!p)
		return -ENOSPC;
	p = xdr_encode_hyper(p, ctx->lifetime);

	/* ctx->ctx_flags */
	p = xdr_encode_hyper(p, ctx->ctx_flags);

	/* ctx->locally_initiated */
	err = gssx_enc_bool(xdr, ctx->locally_initiated);
	if (err)
		return err;

	/* ctx->open */
	err = gssx_enc_bool(xdr, ctx->open);
	if (err)
		return err;

	/* leave options empty for now, will add once we have any options
	 * to pass up at all */
	/* ctx->options */
	err = dummy_enc_opt_array(xdr, &ctx->options);

	return err;
}