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
struct nfsd4_copy {int /*<<< orphan*/  cp_synchronous; int /*<<< orphan*/  cp_res; } ;
struct nfsd4_compoundres {int /*<<< orphan*/  xdr; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 scalar_t__ nfsd42_encode_write_res (struct nfsd4_compoundres*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_one ; 
 scalar_t__* xdr_reserve_space (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static __be32
nfsd4_encode_copy(struct nfsd4_compoundres *resp, __be32 nfserr,
		  struct nfsd4_copy *copy)
{
	__be32 *p;

	nfserr = nfsd42_encode_write_res(resp, &copy->cp_res,
			copy->cp_synchronous);
	if (nfserr)
		return nfserr;

	p = xdr_reserve_space(&resp->xdr, 4 + 4);
	*p++ = xdr_one; /* cr_consecutive */
	*p++ = cpu_to_be32(copy->cp_synchronous);
	return 0;
}