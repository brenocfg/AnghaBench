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
typedef  int u32 ;
struct nfsd4_compoundargs {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int NFS4_SHARE_DENY_BOTH ; 
 int /*<<< orphan*/  READ_BUF (int) ; 
 int be32_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_ok ; 
 int /*<<< orphan*/  nfserr_bad_xdr ; 

__attribute__((used)) static __be32 nfsd4_decode_share_deny(struct nfsd4_compoundargs *argp, u32 *x)
{
	__be32 *p;

	READ_BUF(4);
	*x = be32_to_cpup(p++);
	/* Note: unlinke access bits, deny bits may be zero. */
	if (*x & ~NFS4_SHARE_DENY_BOTH)
		return nfserr_bad_xdr;
	return nfs_ok;
xdr_error:
	return nfserr_bad_xdr;
}