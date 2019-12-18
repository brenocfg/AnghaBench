#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ cr_flavor; } ;
struct svc_rqst {scalar_t__ rq_gssclient; TYPE_1__ rq_cred; } ;
struct svc_export {int ex_nflavors; scalar_t__ ex_client; struct exp_flavor_info* ex_flavors; } ;
struct exp_flavor_info {scalar_t__ pseudoflavor; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ RPC_AUTH_NULL ; 
 scalar_t__ RPC_AUTH_UNIX ; 
 scalar_t__ nfsd4_spo_must_allow (struct svc_rqst*) ; 
 int /*<<< orphan*/  nfserr_wrongsec ; 

__be32 check_nfsd_access(struct svc_export *exp, struct svc_rqst *rqstp)
{
	struct exp_flavor_info *f;
	struct exp_flavor_info *end = exp->ex_flavors + exp->ex_nflavors;

	/* legacy gss-only clients are always OK: */
	if (exp->ex_client == rqstp->rq_gssclient)
		return 0;
	/* ip-address based client; check sec= export option: */
	for (f = exp->ex_flavors; f < end; f++) {
		if (f->pseudoflavor == rqstp->rq_cred.cr_flavor)
			return 0;
	}
	/* defaults in absence of sec= options: */
	if (exp->ex_nflavors == 0) {
		if (rqstp->rq_cred.cr_flavor == RPC_AUTH_NULL ||
		    rqstp->rq_cred.cr_flavor == RPC_AUTH_UNIX)
			return 0;
	}

	/* If the compound op contains a spo_must_allowed op,
	 * it will be sent with integrity/protection which
	 * will have to be expressly allowed on mounts that
	 * don't support it
	 */

	if (nfsd4_spo_must_allow(rqstp))
		return 0;

	return nfserr_wrongsec;
}