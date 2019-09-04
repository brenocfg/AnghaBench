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
struct vpfe_ipipe_cfa {int /*<<< orphan*/  alg; } ;
struct TYPE_2__ {struct vpfe_ipipe_cfa cfa; } ;
struct vpfe_ipipe_device {int /*<<< orphan*/  base_addr; TYPE_1__ config; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  VPFE_IPIPE_CFA_ALG_2DIRAC ; 
 int /*<<< orphan*/  ipipe_set_cfa_regs (int /*<<< orphan*/ ,struct vpfe_ipipe_cfa*) ; 
 scalar_t__ ipipe_validate_cfa_params (struct vpfe_ipipe_cfa*) ; 
 int /*<<< orphan*/  memcpy (struct vpfe_ipipe_cfa*,struct vpfe_ipipe_cfa*,int) ; 
 int /*<<< orphan*/  memset (struct vpfe_ipipe_cfa*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ipipe_set_cfa_params(struct vpfe_ipipe_device *ipipe, void *param)
{
	struct vpfe_ipipe_cfa *cfa_param = param;
	struct vpfe_ipipe_cfa *cfa = &ipipe->config.cfa;

	if (!cfa_param) {
		memset(cfa, 0, sizeof(struct vpfe_ipipe_cfa));
		cfa->alg = VPFE_IPIPE_CFA_ALG_2DIRAC;
		goto success;
	}

	memcpy(cfa, cfa_param, sizeof(struct vpfe_ipipe_cfa));
	if (ipipe_validate_cfa_params(cfa) < 0)
		return -EINVAL;

success:
	ipipe_set_cfa_regs(ipipe->base_addr, cfa);

	return 0;
}