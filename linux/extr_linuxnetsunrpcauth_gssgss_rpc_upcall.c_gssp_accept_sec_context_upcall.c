#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct xdr_netobj {TYPE_11__* data; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; int /*<<< orphan*/  len; } ;
struct svc_cred {void* cr_targ_princ; void* cr_principal; void* cr_raw_principal; } ;
struct rpc_message {int /*<<< orphan*/ * rpc_cred; struct gssx_res_accept_sec_context* rpc_resp; struct gssx_arg_accept_sec_context* rpc_argp; int /*<<< orphan*/ * rpc_proc; } ;
struct net {int dummy; } ;
struct TYPE_23__ {int count; TYPE_11__* data; } ;
struct TYPE_17__ {int /*<<< orphan*/  minor_status; int /*<<< orphan*/  major_status; } ;
struct gssx_res_accept_sec_context {TYPE_9__ options; struct gssx_ctx* context_handle; TYPE_3__ status; TYPE_2__* output_token; } ;
struct TYPE_22__ {struct xdr_netobj display_name; } ;
struct TYPE_21__ {struct xdr_netobj display_name; } ;
struct TYPE_20__ {TYPE_11__* data; int /*<<< orphan*/  len; } ;
struct TYPE_18__ {int /*<<< orphan*/  len; } ;
struct TYPE_15__ {scalar_t__ len; } ;
struct gssx_ctx {TYPE_8__ targ_name; TYPE_7__ src_name; TYPE_6__ mech; TYPE_4__ exported_context_token; TYPE_1__ state; } ;
struct gssx_arg_accept_sec_context {struct gssx_ctx* context_handle; int /*<<< orphan*/  input_token; } ;
struct TYPE_19__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_16__ {int /*<<< orphan*/  len; } ;
struct gssp_upcall_data {int found_creds; struct svc_cred creds; TYPE_5__ mech_oid; TYPE_4__ out_handle; int /*<<< orphan*/  minor_status; int /*<<< orphan*/  major_status; TYPE_1__ in_handle; TYPE_2__ out_token; int /*<<< orphan*/  in_token; } ;
struct TYPE_13__ {int len; TYPE_11__* data; } ;
typedef  TYPE_10__ gssx_buffer ;
struct TYPE_14__ {TYPE_10__ value; } ;

/* Variables and functions */
 size_t GSSX_ACCEPT_SEC_CONTEXT ; 
 int /*<<< orphan*/  GSSX_max_output_handle_sz ; 
 int /*<<< orphan*/  GSSX_max_output_token_sz ; 
 int /*<<< orphan*/  GSSX_max_princ_sz ; 
 int /*<<< orphan*/  GSS_OID_MAX_LEN ; 
 int gssp_alloc_receive_pages (struct gssx_arg_accept_sec_context*) ; 
 int gssp_call (struct net*,struct rpc_message*) ; 
 int /*<<< orphan*/  gssp_free_receive_pages (struct gssx_arg_accept_sec_context*) ; 
 int /*<<< orphan*/  gssp_hostbased_service (void**) ; 
 int /*<<< orphan*/ * gssp_procedures ; 
 void* gssp_stringify (struct xdr_netobj*) ; 
 int /*<<< orphan*/  kfree (TYPE_11__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_11__*,int /*<<< orphan*/ ) ; 

int gssp_accept_sec_context_upcall(struct net *net,
				struct gssp_upcall_data *data)
{
	struct gssx_ctx ctxh = {
		.state = data->in_handle
	};
	struct gssx_arg_accept_sec_context arg = {
		.input_token = data->in_token,
	};
	struct gssx_ctx rctxh = {
		/*
		 * pass in the max length we expect for each of these
		 * buffers but let the xdr code kmalloc them:
		 */
		.exported_context_token.len = GSSX_max_output_handle_sz,
		.mech.len = GSS_OID_MAX_LEN,
		.targ_name.display_name.len = GSSX_max_princ_sz,
		.src_name.display_name.len = GSSX_max_princ_sz
	};
	struct gssx_res_accept_sec_context res = {
		.context_handle = &rctxh,
		.output_token = &data->out_token
	};
	struct rpc_message msg = {
		.rpc_proc = &gssp_procedures[GSSX_ACCEPT_SEC_CONTEXT],
		.rpc_argp = &arg,
		.rpc_resp = &res,
		.rpc_cred = NULL, /* FIXME ? */
	};
	struct xdr_netobj client_name = { 0 , NULL };
	struct xdr_netobj target_name = { 0, NULL };
	int ret;

	if (data->in_handle.len != 0)
		arg.context_handle = &ctxh;
	res.output_token->len = GSSX_max_output_token_sz;

	ret = gssp_alloc_receive_pages(&arg);
	if (ret)
		return ret;

	ret = gssp_call(net, &msg);

	gssp_free_receive_pages(&arg);

	/* we need to fetch all data even in case of error so
	 * that we can free special strctures is they have been allocated */
	data->major_status = res.status.major_status;
	data->minor_status = res.status.minor_status;
	if (res.context_handle) {
		data->out_handle = rctxh.exported_context_token;
		data->mech_oid.len = rctxh.mech.len;
		if (rctxh.mech.data) {
			memcpy(data->mech_oid.data, rctxh.mech.data,
						data->mech_oid.len);
			kfree(rctxh.mech.data);
		}
		client_name = rctxh.src_name.display_name;
		target_name = rctxh.targ_name.display_name;
	}

	if (res.options.count == 1) {
		gssx_buffer *value = &res.options.data[0].value;
		/* Currently we only decode CREDS_VALUE, if we add
		 * anything else we'll have to loop and match on the
		 * option name */
		if (value->len == 1) {
			/* steal group info from struct svc_cred */
			data->creds = *(struct svc_cred *)value->data;
			data->found_creds = 1;
		}
		/* whether we use it or not, free data */
		kfree(value->data);
	}

	if (res.options.count != 0) {
		kfree(res.options.data);
	}

	/* convert to GSS_NT_HOSTBASED_SERVICE form and set into creds */
	if (data->found_creds) {
		if (client_name.data) {
			data->creds.cr_raw_principal =
					gssp_stringify(&client_name);
			data->creds.cr_principal =
					gssp_stringify(&client_name);
			gssp_hostbased_service(&data->creds.cr_principal);
		}
		if (target_name.data) {
			data->creds.cr_targ_princ =
					gssp_stringify(&target_name);
			gssp_hostbased_service(&data->creds.cr_targ_princ);
		}
	}
	kfree(client_name.data);
	kfree(target_name.data);

	return ret;
}