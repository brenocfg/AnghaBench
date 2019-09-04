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
struct vpfe_ipipe_gbce {int /*<<< orphan*/  table; int /*<<< orphan*/  type; int /*<<< orphan*/  en; } ;
struct TYPE_2__ {struct vpfe_ipipe_gbce gbce; } ;
struct vpfe_ipipe_device {TYPE_1__ config; } ;

/* Variables and functions */
 int VPFE_IPIPE_MAX_SIZE_GBCE_LUT ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ipipe_get_gbce_params(struct vpfe_ipipe_device *ipipe, void *param)
{
	struct vpfe_ipipe_gbce *gbce_param = param;
	struct vpfe_ipipe_gbce *gbce = &ipipe->config.gbce;

	gbce_param->en = gbce->en;
	gbce_param->type = gbce->type;

	memcpy(gbce_param->table, gbce->table,
		(VPFE_IPIPE_MAX_SIZE_GBCE_LUT * sizeof(unsigned short)));

	return 0;
}