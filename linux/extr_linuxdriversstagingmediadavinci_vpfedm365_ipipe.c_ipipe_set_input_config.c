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
struct vpfe_ipipe_input_config {int dummy; } ;
struct TYPE_2__ {struct vpfe_ipipe_input_config input_config; } ;
struct vpfe_ipipe_device {TYPE_1__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct vpfe_ipipe_input_config*,void*,int) ; 
 int /*<<< orphan*/  memset (struct vpfe_ipipe_input_config*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ipipe_set_input_config(struct vpfe_ipipe_device *ipipe, void *param)
{
	struct vpfe_ipipe_input_config *config = &ipipe->config.input_config;

	if (!param)
		memset(config, 0, sizeof(struct vpfe_ipipe_input_config));
	else
		memcpy(config, param, sizeof(struct vpfe_ipipe_input_config));
	return 0;
}