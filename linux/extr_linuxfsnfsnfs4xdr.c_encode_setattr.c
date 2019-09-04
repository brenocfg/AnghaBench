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
struct nfs_setattrargs {int /*<<< orphan*/  label; int /*<<< orphan*/  iap; int /*<<< orphan*/  stateid; } ;
struct nfs_server {int /*<<< orphan*/  attr_bitmask; } ;
struct compound_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_SETATTR ; 
 int /*<<< orphan*/  decode_setattr_maxsz ; 
 int /*<<< orphan*/  encode_attrs (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct nfs_server const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_nfs4_stateid (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encode_op_hdr (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct compound_hdr*) ; 

__attribute__((used)) static void encode_setattr(struct xdr_stream *xdr, const struct nfs_setattrargs *arg, const struct nfs_server *server, struct compound_hdr *hdr)
{
	encode_op_hdr(xdr, OP_SETATTR, decode_setattr_maxsz, hdr);
	encode_nfs4_stateid(xdr, &arg->stateid);
	encode_attrs(xdr, arg->iap, arg->label, NULL, server,
			server->attr_bitmask);
}