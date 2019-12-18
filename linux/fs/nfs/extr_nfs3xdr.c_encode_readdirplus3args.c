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
struct nfs3_readdirargs {int count; int /*<<< orphan*/  verf; int /*<<< orphan*/  cookie; int /*<<< orphan*/  fh; } ;
typedef  void* __be32 ;

/* Variables and functions */
 scalar_t__ NFS3_COOKIEVERFSIZE ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  encode_nfs_fh3 (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 void** xdr_encode_cookie3 (void**,int /*<<< orphan*/ ) ; 
 void** xdr_encode_cookieverf3 (void**,int /*<<< orphan*/ ) ; 
 void** xdr_reserve_space (struct xdr_stream*,scalar_t__) ; 

__attribute__((used)) static void encode_readdirplus3args(struct xdr_stream *xdr,
				    const struct nfs3_readdirargs *args)
{
	__be32 *p;

	encode_nfs_fh3(xdr, args->fh);

	p = xdr_reserve_space(xdr, 8 + NFS3_COOKIEVERFSIZE + 4 + 4);
	p = xdr_encode_cookie3(p, args->cookie);
	p = xdr_encode_cookieverf3(p, args->verf);

	/*
	 * readdirplus: need dircount + buffer size.
	 * We just make sure we make dircount big enough
	 */
	*p++ = cpu_to_be32(args->count >> 3);

	*p = cpu_to_be32(args->count);
}