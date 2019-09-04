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
struct svc_rqst {TYPE_1__ rq_cred; } ;
struct svc_export {int ex_nflavors; int ex_flags; struct exp_flavor_info* ex_flavors; } ;
struct exp_flavor_info {scalar_t__ pseudoflavor; int flags; } ;

/* Variables and functions */

int nfsexp_flags(struct svc_rqst *rqstp, struct svc_export *exp)
{
	struct exp_flavor_info *f;
	struct exp_flavor_info *end = exp->ex_flavors + exp->ex_nflavors;

	for (f = exp->ex_flavors; f < end; f++) {
		if (f->pseudoflavor == rqstp->rq_cred.cr_flavor)
			return f->flags;
	}
	return exp->ex_flags;

}