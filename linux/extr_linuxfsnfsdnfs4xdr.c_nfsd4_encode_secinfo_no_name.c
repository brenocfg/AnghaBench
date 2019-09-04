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
struct nfsd4_secinfo_no_name {int /*<<< orphan*/  sin_exp; } ;
struct nfsd4_compoundres {struct xdr_stream xdr; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  nfsd4_do_encode_secinfo (struct xdr_stream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be32
nfsd4_encode_secinfo_no_name(struct nfsd4_compoundres *resp, __be32 nfserr,
		     struct nfsd4_secinfo_no_name *secinfo)
{
	struct xdr_stream *xdr = &resp->xdr;

	return nfsd4_do_encode_secinfo(xdr, secinfo->sin_exp);
}