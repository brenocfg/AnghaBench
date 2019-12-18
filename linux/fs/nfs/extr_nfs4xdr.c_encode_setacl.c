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
struct nfs_setaclargs {int acl_len; int /*<<< orphan*/  acl_pages; } ;
struct compound_hdr {int dummy; } ;
typedef  void* __be32 ;

/* Variables and functions */
 int FATTR4_WORD0_ACL ; 
 int /*<<< orphan*/  OP_SETATTR ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  decode_setacl_maxsz ; 
 int /*<<< orphan*/  encode_nfs4_stateid (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encode_op_hdr (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct compound_hdr*) ; 
 void** reserve_space (struct xdr_stream*,int) ; 
 int /*<<< orphan*/  xdr_write_pages (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zero_stateid ; 

__attribute__((used)) static void
encode_setacl(struct xdr_stream *xdr, const struct nfs_setaclargs *arg,
		struct compound_hdr *hdr)
{
	__be32 *p;

	encode_op_hdr(xdr, OP_SETATTR, decode_setacl_maxsz, hdr);
	encode_nfs4_stateid(xdr, &zero_stateid);
	p = reserve_space(xdr, 2*4);
	*p++ = cpu_to_be32(1);
	*p = cpu_to_be32(FATTR4_WORD0_ACL);
	p = reserve_space(xdr, 4);
	*p = cpu_to_be32(arg->acl_len);
	xdr_write_pages(xdr, arg->acl_pages, 0, arg->acl_len);
}