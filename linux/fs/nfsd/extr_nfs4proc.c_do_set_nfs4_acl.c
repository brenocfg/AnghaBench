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
struct svc_rqst {int dummy; } ;
struct svc_fh {int dummy; } ;
struct nfs4_acl {int dummy; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  FATTR4_WORD0_ACL ; 
 scalar_t__ nfsd4_set_nfs4_acl (struct svc_rqst*,struct svc_fh*,struct nfs4_acl*) ; 

__attribute__((used)) static void
do_set_nfs4_acl(struct svc_rqst *rqstp, struct svc_fh *fhp,
		struct nfs4_acl *acl, u32 *bmval)
{
	__be32 status;

	status = nfsd4_set_nfs4_acl(rqstp, fhp, acl);
	if (status)
		/*
		 * We should probably fail the whole open at this point,
		 * but we've already created the file, so it's too late;
		 * So this seems the least of evils:
		 */
		bmval[0] &= ~FATTR4_WORD0_ACL;
}