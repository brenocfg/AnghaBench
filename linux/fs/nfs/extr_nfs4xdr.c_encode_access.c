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
typedef  int /*<<< orphan*/  u32 ;
struct xdr_stream {int dummy; } ;
struct compound_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_ACCESS ; 
 int /*<<< orphan*/  decode_access_maxsz ; 
 int /*<<< orphan*/  encode_op_hdr (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_uint32 (struct xdr_stream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void encode_access(struct xdr_stream *xdr, u32 access, struct compound_hdr *hdr)
{
	encode_op_hdr(xdr, OP_ACCESS, decode_access_maxsz, hdr);
	encode_uint32(xdr, access);
}