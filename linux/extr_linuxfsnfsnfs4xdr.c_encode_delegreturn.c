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
struct compound_hdr {int dummy; } ;
typedef  int /*<<< orphan*/  nfs4_stateid ;

/* Variables and functions */
 int /*<<< orphan*/  OP_DELEGRETURN ; 
 int /*<<< orphan*/  decode_delegreturn_maxsz ; 
 int /*<<< orphan*/  encode_nfs4_stateid (struct xdr_stream*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  encode_op_hdr (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct compound_hdr*) ; 

__attribute__((used)) static void encode_delegreturn(struct xdr_stream *xdr, const nfs4_stateid *stateid, struct compound_hdr *hdr)
{
	encode_op_hdr(xdr, OP_DELEGRETURN, decode_delegreturn_maxsz, hdr);
	encode_nfs4_stateid(xdr, stateid);
}