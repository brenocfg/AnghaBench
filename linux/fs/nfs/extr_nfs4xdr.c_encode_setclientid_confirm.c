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
struct nfs4_setclientid_res {int /*<<< orphan*/  confirm; int /*<<< orphan*/  clientid; } ;
struct compound_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_SETCLIENTID_CONFIRM ; 
 int /*<<< orphan*/  decode_setclientid_confirm_maxsz ; 
 int /*<<< orphan*/  encode_nfs4_verifier (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encode_op_hdr (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_uint64 (struct xdr_stream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void encode_setclientid_confirm(struct xdr_stream *xdr, const struct nfs4_setclientid_res *arg, struct compound_hdr *hdr)
{
	encode_op_hdr(xdr, OP_SETCLIENTID_CONFIRM,
			decode_setclientid_confirm_maxsz, hdr);
	encode_uint64(xdr, arg->clientid);
	encode_nfs4_verifier(xdr, &arg->confirm);
}