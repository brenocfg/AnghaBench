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
struct nfs4_setclientid {TYPE_1__* sc_clnt; int /*<<< orphan*/  sc_uaddr; int /*<<< orphan*/  sc_uaddr_len; int /*<<< orphan*/  sc_netid; int /*<<< orphan*/  sc_netid_len; int /*<<< orphan*/  sc_prog; int /*<<< orphan*/  sc_verifier; } ;
struct compound_hdr {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  cl_cb_ident; int /*<<< orphan*/  cl_owner_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_SETCLIENTID ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decode_setclientid_maxsz ; 
 int /*<<< orphan*/  encode_nfs4_verifier (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_op_hdr (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_string (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * reserve_space (struct xdr_stream*,int) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void encode_setclientid(struct xdr_stream *xdr, const struct nfs4_setclientid *setclientid, struct compound_hdr *hdr)
{
	__be32 *p;

	encode_op_hdr(xdr, OP_SETCLIENTID, decode_setclientid_maxsz, hdr);
	encode_nfs4_verifier(xdr, setclientid->sc_verifier);

	encode_string(xdr, strlen(setclientid->sc_clnt->cl_owner_id),
			setclientid->sc_clnt->cl_owner_id);
	p = reserve_space(xdr, 4);
	*p = cpu_to_be32(setclientid->sc_prog);
	encode_string(xdr, setclientid->sc_netid_len, setclientid->sc_netid);
	encode_string(xdr, setclientid->sc_uaddr_len, setclientid->sc_uaddr);
	p = reserve_space(xdr, 4);
	*p = cpu_to_be32(setclientid->sc_clnt->cl_cb_ident);
}