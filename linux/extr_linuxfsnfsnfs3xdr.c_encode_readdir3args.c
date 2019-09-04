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
struct nfs3_readdirargs {int /*<<< orphan*/  count; int /*<<< orphan*/  verf; int /*<<< orphan*/  cookie; int /*<<< orphan*/  fh; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ NFS3_COOKIEVERFSIZE ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_nfs_fh3 (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_encode_cookie3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_encode_cookieverf3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,scalar_t__) ; 

__attribute__((used)) static void encode_readdir3args(struct xdr_stream *xdr,
				const struct nfs3_readdirargs *args)
{
	__be32 *p;

	encode_nfs_fh3(xdr, args->fh);

	p = xdr_reserve_space(xdr, 8 + NFS3_COOKIEVERFSIZE + 4);
	p = xdr_encode_cookie3(p, args->cookie);
	p = xdr_encode_cookieverf3(p, args->verf);
	*p = cpu_to_be32(args->count);
}