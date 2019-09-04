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
struct rpc_rqst {int dummy; } ;
struct nfs4_readlink {int dummy; } ;
struct compound_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_READLINK ; 
 int /*<<< orphan*/  decode_readlink_maxsz ; 
 int /*<<< orphan*/  encode_op_hdr (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct compound_hdr*) ; 

__attribute__((used)) static void encode_readlink(struct xdr_stream *xdr, const struct nfs4_readlink *readlink, struct rpc_rqst *req, struct compound_hdr *hdr)
{
	encode_op_hdr(xdr, OP_READLINK, decode_readlink_maxsz, hdr);
}