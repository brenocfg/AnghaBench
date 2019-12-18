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
struct svc_rqst {int dummy; } ;
struct svc_fh {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dentry; } ;
struct svc_export {TYPE_1__ ex_path; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct svc_export*) ; 
 int /*<<< orphan*/  PTR_ERR (struct svc_export*) ; 
 int /*<<< orphan*/  exp_put (struct svc_export*) ; 
 int /*<<< orphan*/  fh_compose (struct svc_fh*,struct svc_export*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfserrno (int /*<<< orphan*/ ) ; 
 struct svc_export* rqst_find_fsidzero_export (struct svc_rqst*) ; 

__be32
exp_pseudoroot(struct svc_rqst *rqstp, struct svc_fh *fhp)
{
	struct svc_export *exp;
	__be32 rv;

	exp = rqst_find_fsidzero_export(rqstp);
	if (IS_ERR(exp))
		return nfserrno(PTR_ERR(exp));
	rv = fh_compose(fhp, exp, exp->ex_path.dentry, NULL);
	exp_put(exp);
	return rv;
}