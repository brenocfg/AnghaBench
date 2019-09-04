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
struct vpfe_ipipe_otfdpc {int dummy; } ;
struct TYPE_2__ {struct vpfe_ipipe_otfdpc otfdpc; } ;
struct vpfe_ipipe_device {TYPE_1__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct vpfe_ipipe_otfdpc*,struct vpfe_ipipe_otfdpc*,int) ; 

__attribute__((used)) static int ipipe_get_otfdpc_params(struct vpfe_ipipe_device *ipipe, void *param)
{
	struct vpfe_ipipe_otfdpc *dpc_param = param;
	struct vpfe_ipipe_otfdpc *otfdpc = &ipipe->config.otfdpc;

	memcpy(dpc_param, otfdpc, sizeof(struct vpfe_ipipe_otfdpc));
	return 0;
}