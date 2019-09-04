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
struct vpfe_ipipe_nf {int dummy; } ;
struct TYPE_2__ {struct vpfe_ipipe_nf nf2; struct vpfe_ipipe_nf nf1; } ;
struct vpfe_ipipe_device {TYPE_1__ config; } ;

/* Variables and functions */
 unsigned int IPIPE_D2F_2ND ; 
 int /*<<< orphan*/  memcpy (struct vpfe_ipipe_nf*,struct vpfe_ipipe_nf*,int) ; 

__attribute__((used)) static int ipipe_get_nf_params(struct vpfe_ipipe_device *ipipe,
			       unsigned int id, void *param)
{
	struct vpfe_ipipe_nf *nf_param = param;
	struct vpfe_ipipe_nf *nf = &ipipe->config.nf1;

	if (id == IPIPE_D2F_2ND)
		nf = &ipipe->config.nf2;

	memcpy(nf_param, nf, sizeof(struct vpfe_ipipe_nf));

	return 0;
}