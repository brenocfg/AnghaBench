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
typedef  int /*<<< orphan*/  clientid4 ;

/* Variables and functions */
 int /*<<< orphan*/  OP_RENEW ; 
 int /*<<< orphan*/  decode_renew_maxsz ; 
 int /*<<< orphan*/  encode_op_hdr (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_uint64 (struct xdr_stream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void encode_renew(struct xdr_stream *xdr, clientid4 clid,
			 struct compound_hdr *hdr)
{
	encode_op_hdr(xdr, OP_RENEW, decode_renew_maxsz, hdr);
	encode_uint64(xdr, clid);
}