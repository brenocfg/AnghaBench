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
struct nfsd4_setattr {int* sa_bmval; } ;
struct nfsd4_compoundres {struct xdr_stream xdr; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 void* cpu_to_be32 (int) ; 
 scalar_t__ nfserr_resource ; 
 scalar_t__* xdr_reserve_space (struct xdr_stream*,int) ; 

__attribute__((used)) static __be32
nfsd4_encode_setattr(struct nfsd4_compoundres *resp, __be32 nfserr, struct nfsd4_setattr *setattr)
{
	struct xdr_stream *xdr = &resp->xdr;
	__be32 *p;

	p = xdr_reserve_space(xdr, 16);
	if (!p)
		return nfserr_resource;
	if (nfserr) {
		*p++ = cpu_to_be32(3);
		*p++ = cpu_to_be32(0);
		*p++ = cpu_to_be32(0);
		*p++ = cpu_to_be32(0);
	}
	else {
		*p++ = cpu_to_be32(3);
		*p++ = cpu_to_be32(setattr->sa_bmval[0]);
		*p++ = cpu_to_be32(setattr->sa_bmval[1]);
		*p++ = cpu_to_be32(setattr->sa_bmval[2]);
	}
	return nfserr;
}