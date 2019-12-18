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
struct xdr_stream {int dummy; } ;
struct rpc_rqst {int dummy; } ;
struct page {int dummy; } ;
struct gssx_res_accept_sec_context {int /*<<< orphan*/  options; int /*<<< orphan*/ * output_token; int /*<<< orphan*/ * context_handle; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 int gssx_dec_bool (struct xdr_stream*,scalar_t__*) ; 
 int gssx_dec_buffer (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int gssx_dec_ctx (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int gssx_dec_option_array (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int gssx_dec_status (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 int /*<<< orphan*/  xdr_set_scratch_buffer (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int gssx_dec_accept_sec_context(struct rpc_rqst *rqstp,
				struct xdr_stream *xdr,
				void *data)
{
	struct gssx_res_accept_sec_context *res = data;
	u32 value_follows;
	int err;
	struct page *scratch;

	scratch = alloc_page(GFP_KERNEL);
	if (!scratch)
		return -ENOMEM;
	xdr_set_scratch_buffer(xdr, page_address(scratch), PAGE_SIZE);

	/* res->status */
	err = gssx_dec_status(xdr, &res->status);
	if (err)
		goto out_free;

	/* res->context_handle */
	err = gssx_dec_bool(xdr, &value_follows);
	if (err)
		goto out_free;
	if (value_follows) {
		err = gssx_dec_ctx(xdr, res->context_handle);
		if (err)
			goto out_free;
	} else {
		res->context_handle = NULL;
	}

	/* res->output_token */
	err = gssx_dec_bool(xdr, &value_follows);
	if (err)
		goto out_free;
	if (value_follows) {
		err = gssx_dec_buffer(xdr, res->output_token);
		if (err)
			goto out_free;
	} else {
		res->output_token = NULL;
	}

	/* res->delegated_cred_handle */
	err = gssx_dec_bool(xdr, &value_follows);
	if (err)
		goto out_free;
	if (value_follows) {
		/* we do not support upcall servers sending this data. */
		err = -EINVAL;
		goto out_free;
	}

	/* res->options */
	err = gssx_dec_option_array(xdr, &res->options);

out_free:
	__free_page(scratch);
	return err;
}