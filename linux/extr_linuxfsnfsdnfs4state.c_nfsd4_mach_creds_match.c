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
struct svc_cred {scalar_t__ cr_gss_mech; int /*<<< orphan*/  cr_principal; int /*<<< orphan*/  cr_raw_principal; } ;
struct svc_rqst {struct svc_cred rq_cred; } ;
struct TYPE_2__ {scalar_t__ cr_gss_mech; scalar_t__ cr_principal; scalar_t__ cr_raw_principal; } ;
struct nfs4_client {TYPE_1__ cl_cred; int /*<<< orphan*/  cl_mach_cred; } ;

/* Variables and functions */
 scalar_t__ strcmp (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_rqst_integrity_protected (struct svc_rqst*) ; 

bool nfsd4_mach_creds_match(struct nfs4_client *cl, struct svc_rqst *rqstp)
{
	struct svc_cred *cr = &rqstp->rq_cred;

	if (!cl->cl_mach_cred)
		return true;
	if (cl->cl_cred.cr_gss_mech != cr->cr_gss_mech)
		return false;
	if (!svc_rqst_integrity_protected(rqstp))
		return false;
	if (cl->cl_cred.cr_raw_principal)
		return 0 == strcmp(cl->cl_cred.cr_raw_principal,
						cr->cr_raw_principal);
	if (!cr->cr_principal)
		return false;
	return 0 == strcmp(cl->cl_cred.cr_principal, cr->cr_principal);
}