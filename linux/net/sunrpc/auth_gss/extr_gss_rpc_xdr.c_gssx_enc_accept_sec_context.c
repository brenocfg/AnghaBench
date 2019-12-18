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
struct xdr_stream {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct rpc_rqst {TYPE_1__ rq_rcv_buf; } ;
struct gssx_arg_accept_sec_context {int npages; int /*<<< orphan*/  pages; int /*<<< orphan*/  options; int /*<<< orphan*/  ret_deleg_cred; scalar_t__ input_cb; int /*<<< orphan*/  input_token; scalar_t__ cred_handle; scalar_t__ context_handle; int /*<<< orphan*/  call_ctx; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  XDRBUF_SPARSE_PAGES ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 int dummy_enc_opt_array (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int gssx_enc_bool (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 int gssx_enc_call_ctx (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int gssx_enc_cb (struct xdr_stream*,scalar_t__) ; 
 int gssx_enc_cred (struct xdr_stream*,scalar_t__) ; 
 int gssx_enc_ctx (struct xdr_stream*,scalar_t__) ; 
 int gssx_enc_in_token (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_inline_pages (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void gssx_enc_accept_sec_context(struct rpc_rqst *req,
				 struct xdr_stream *xdr,
				 const void *data)
{
	const struct gssx_arg_accept_sec_context *arg = data;
	int err;

	err = gssx_enc_call_ctx(xdr, &arg->call_ctx);
	if (err)
		goto done;

	/* arg->context_handle */
	if (arg->context_handle)
		err = gssx_enc_ctx(xdr, arg->context_handle);
	else
		err = gssx_enc_bool(xdr, 0);
	if (err)
		goto done;

	/* arg->cred_handle */
	if (arg->cred_handle)
		err = gssx_enc_cred(xdr, arg->cred_handle);
	else
		err = gssx_enc_bool(xdr, 0);
	if (err)
		goto done;

	/* arg->input_token */
	err = gssx_enc_in_token(xdr, &arg->input_token);
	if (err)
		goto done;

	/* arg->input_cb */
	if (arg->input_cb)
		err = gssx_enc_cb(xdr, arg->input_cb);
	else
		err = gssx_enc_bool(xdr, 0);
	if (err)
		goto done;

	err = gssx_enc_bool(xdr, arg->ret_deleg_cred);
	if (err)
		goto done;

	/* leave options empty for now, will add once we have any options
	 * to pass up at all */
	/* arg->options */
	err = dummy_enc_opt_array(xdr, &arg->options);

	xdr_inline_pages(&req->rq_rcv_buf,
		PAGE_SIZE/2 /* pretty arbitrary */,
		arg->pages, 0 /* page base */, arg->npages * PAGE_SIZE);
	req->rq_rcv_buf.flags |= XDRBUF_SPARSE_PAGES;
done:
	if (err)
		dprintk("RPC:       gssx_enc_accept_sec_context: %d\n", err);
}