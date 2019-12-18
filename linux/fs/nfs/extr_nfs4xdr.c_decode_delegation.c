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
typedef  int uint32_t ;
struct xdr_stream {int dummy; } ;
struct nfs_openres {scalar_t__ delegation_type; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EIO ; 
#define  NFS4_OPEN_DELEGATE_NONE 131 
#define  NFS4_OPEN_DELEGATE_NONE_EXT 130 
#define  NFS4_OPEN_DELEGATE_READ 129 
#define  NFS4_OPEN_DELEGATE_WRITE 128 
 int be32_to_cpup (int /*<<< orphan*/ *) ; 
 int decode_no_delegation (struct xdr_stream*,struct nfs_openres*) ; 
 int decode_rw_delegation (struct xdr_stream*,int,struct nfs_openres*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/ * xdr_inline_decode (struct xdr_stream*,int) ; 

__attribute__((used)) static int decode_delegation(struct xdr_stream *xdr, struct nfs_openres *res)
{
	__be32 *p;
	uint32_t delegation_type;

	p = xdr_inline_decode(xdr, 4);
	if (unlikely(!p))
		return -EIO;
	delegation_type = be32_to_cpup(p);
	res->delegation_type = 0;
	switch (delegation_type) {
	case NFS4_OPEN_DELEGATE_NONE:
		return 0;
	case NFS4_OPEN_DELEGATE_READ:
	case NFS4_OPEN_DELEGATE_WRITE:
		return decode_rw_delegation(xdr, delegation_type, res);
	case NFS4_OPEN_DELEGATE_NONE_EXT:
		return decode_no_delegation(xdr, res);
	}
	return -EIO;
}