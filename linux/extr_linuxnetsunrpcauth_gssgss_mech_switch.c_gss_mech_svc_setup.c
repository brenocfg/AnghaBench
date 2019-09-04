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
struct pf_desc {int /*<<< orphan*/ * auth_domain_name; int /*<<< orphan*/  pseudoflavor; int /*<<< orphan*/  name; } ;
struct gss_api_mech {int gm_pf_num; struct pf_desc* gm_pfs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  gss_mech_free (struct gss_api_mech*) ; 
 int /*<<< orphan*/ * make_auth_domain_name (int /*<<< orphan*/ ) ; 
 int svcauth_gss_register_pseudoflavor (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
gss_mech_svc_setup(struct gss_api_mech *gm)
{
	struct pf_desc *pf;
	int i, status;

	for (i = 0; i < gm->gm_pf_num; i++) {
		pf = &gm->gm_pfs[i];
		pf->auth_domain_name = make_auth_domain_name(pf->name);
		status = -ENOMEM;
		if (pf->auth_domain_name == NULL)
			goto out;
		status = svcauth_gss_register_pseudoflavor(pf->pseudoflavor,
							pf->auth_domain_name);
		if (status)
			goto out;
	}
	return 0;
out:
	gss_mech_free(gm);
	return status;
}