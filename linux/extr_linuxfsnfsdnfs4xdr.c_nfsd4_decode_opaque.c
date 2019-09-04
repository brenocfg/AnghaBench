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
struct xdr_netobj {int len; int /*<<< orphan*/  data; } ;
struct nfsd4_compoundargs {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int NFS4_OPAQUE_LIMIT ; 
 int /*<<< orphan*/  READ_BUF (int) ; 
 int /*<<< orphan*/  SAVEMEM (int /*<<< orphan*/ ,int) ; 
 int be32_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_ok ; 
 int /*<<< orphan*/  nfserr_bad_xdr ; 

__attribute__((used)) static __be32 nfsd4_decode_opaque(struct nfsd4_compoundargs *argp, struct xdr_netobj *o)
{
	__be32 *p;

	READ_BUF(4);
	o->len = be32_to_cpup(p++);

	if (o->len == 0 || o->len > NFS4_OPAQUE_LIMIT)
		return nfserr_bad_xdr;

	READ_BUF(o->len);
	SAVEMEM(o->data, o->len);
	return nfs_ok;
xdr_error:
	return nfserr_bad_xdr;
}