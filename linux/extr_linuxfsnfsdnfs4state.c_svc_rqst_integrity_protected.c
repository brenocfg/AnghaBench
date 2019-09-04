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
typedef  scalar_t__ u32 ;
struct svc_cred {int /*<<< orphan*/  cr_flavor; int /*<<< orphan*/  cr_gss_mech; } ;
struct svc_rqst {struct svc_cred rq_cred; } ;

/* Variables and functions */
 scalar_t__ RPC_GSS_SVC_INTEGRITY ; 
 scalar_t__ RPC_GSS_SVC_PRIVACY ; 
 scalar_t__ gss_pseudoflavor_to_service (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool svc_rqst_integrity_protected(struct svc_rqst *rqstp)
{
	struct svc_cred *cr = &rqstp->rq_cred;
	u32 service;

	if (!cr->cr_gss_mech)
		return false;
	service = gss_pseudoflavor_to_service(cr->cr_gss_mech, cr->cr_flavor);
	return service == RPC_GSS_SVC_INTEGRITY ||
	       service == RPC_GSS_SVC_PRIVACY;
}