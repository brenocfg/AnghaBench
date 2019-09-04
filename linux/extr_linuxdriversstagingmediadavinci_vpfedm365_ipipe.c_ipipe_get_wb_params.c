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
struct vpfe_ipipe_wb {int dummy; } ;
struct TYPE_2__ {struct vpfe_ipipe_wb wbal; } ;
struct vpfe_ipipe_device {TYPE_1__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct vpfe_ipipe_wb*,struct vpfe_ipipe_wb*,int) ; 

__attribute__((used)) static int ipipe_get_wb_params(struct vpfe_ipipe_device *ipipe, void *param)
{
	struct vpfe_ipipe_wb *wb_param = param;
	struct vpfe_ipipe_wb *wbal = &ipipe->config.wbal;

	memcpy(wb_param, wbal, sizeof(struct vpfe_ipipe_wb));
	return 0;
}