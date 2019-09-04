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
struct xdr_stream {long end; long p; } ;
struct svc_rqst {int dummy; } ;
struct cb_process_state {int minorversion; scalar_t__ drc_status; } ;
struct callback_op {scalar_t__ (* decode_args ) (struct svc_rqst*,struct xdr_stream*,void*) ;scalar_t__ (* process_op ) (void*,void*,struct cb_process_state*) ;scalar_t__ (* encode_res ) (struct svc_rqst*,struct xdr_stream*,void*) ;} ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4ERR_MINOR_VERS_MISMATCH ; 
 int /*<<< orphan*/  NFS4ERR_OP_ILLEGAL ; 
 int /*<<< orphan*/  NFS4ERR_RESOURCE ; 
 unsigned int OP_CB_ILLEGAL ; 
 long PAGE_SIZE ; 
 struct callback_op* callback_ops ; 
 scalar_t__ decode_op_hdr (struct xdr_stream*,unsigned int*) ; 
 scalar_t__ encode_op_hdr (struct xdr_stream*,unsigned int,scalar_t__) ; 
 scalar_t__ htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ preprocess_nfs41_op (int,unsigned int,struct callback_op**) ; 
 scalar_t__ preprocess_nfs42_op (int,unsigned int,struct callback_op**) ; 
 scalar_t__ preprocess_nfs4_op (unsigned int,struct callback_op**) ; 
 scalar_t__ stub1 (struct svc_rqst*,struct xdr_stream*,void*) ; 
 scalar_t__ stub2 (void*,void*,struct cb_process_state*) ; 
 scalar_t__ stub3 (struct svc_rqst*,struct xdr_stream*,void*) ; 
 scalar_t__ unlikely (scalar_t__) ; 

__attribute__((used)) static __be32 process_op(int nop, struct svc_rqst *rqstp,
		struct xdr_stream *xdr_in, void *argp,
		struct xdr_stream *xdr_out, void *resp,
		struct cb_process_state *cps)
{
	struct callback_op *op = &callback_ops[0];
	unsigned int op_nr;
	__be32 status;
	long maxlen;
	__be32 res;

	status = decode_op_hdr(xdr_in, &op_nr);
	if (unlikely(status))
		return status;

	switch (cps->minorversion) {
	case 0:
		status = preprocess_nfs4_op(op_nr, &op);
		break;
	case 1:
		status = preprocess_nfs41_op(nop, op_nr, &op);
		break;
	case 2:
		status = preprocess_nfs42_op(nop, op_nr, &op);
		break;
	default:
		status = htonl(NFS4ERR_MINOR_VERS_MISMATCH);
	}

	if (status == htonl(NFS4ERR_OP_ILLEGAL))
		op_nr = OP_CB_ILLEGAL;
	if (status)
		goto encode_hdr;

	if (cps->drc_status) {
		status = cps->drc_status;
		goto encode_hdr;
	}

	maxlen = xdr_out->end - xdr_out->p;
	if (maxlen > 0 && maxlen < PAGE_SIZE) {
		status = op->decode_args(rqstp, xdr_in, argp);
		if (likely(status == 0))
			status = op->process_op(argp, resp, cps);
	} else
		status = htonl(NFS4ERR_RESOURCE);

encode_hdr:
	res = encode_op_hdr(xdr_out, op_nr, status);
	if (unlikely(res))
		return res;
	if (op->encode_res != NULL && status == 0)
		status = op->encode_res(rqstp, xdr_out, resp);
	return status;
}