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
struct nfs_open_confirmargs {int /*<<< orphan*/  seqid; int /*<<< orphan*/  stateid; } ;
struct compound_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_OPEN_CONFIRM ; 
 int /*<<< orphan*/  decode_open_confirm_maxsz ; 
 int /*<<< orphan*/  encode_nfs4_seqid (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_nfs4_stateid (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_op_hdr (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct compound_hdr*) ; 

__attribute__((used)) static void encode_open_confirm(struct xdr_stream *xdr, const struct nfs_open_confirmargs *arg, struct compound_hdr *hdr)
{
	encode_op_hdr(xdr, OP_OPEN_CONFIRM, decode_open_confirm_maxsz, hdr);
	encode_nfs4_stateid(xdr, arg->stateid);
	encode_nfs4_seqid(xdr, arg->seqid);
}