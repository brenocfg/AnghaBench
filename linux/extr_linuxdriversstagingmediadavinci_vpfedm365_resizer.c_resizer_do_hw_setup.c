#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct TYPE_5__ {scalar_t__ output; } ;
struct TYPE_4__ {scalar_t__ output; } ;
struct resizer_params {int dummy; } ;
struct vpfe_resizer_device {TYPE_2__ resizer_b; TYPE_1__ resizer_a; struct resizer_params config; } ;
struct TYPE_6__ {scalar_t__ input; scalar_t__ output; } ;
struct vpfe_device {TYPE_3__ vpfe_ipipeif; } ;

/* Variables and functions */
 scalar_t__ IPIPEIF_INPUT_MEMORY ; 
 scalar_t__ IPIPEIF_OUTPUT_RESIZER ; 
 scalar_t__ RESIZER_OUTPUT_MEMORY ; 
 int config_rsz_hw (struct vpfe_resizer_device*,struct resizer_params*) ; 
 int resizer_configure_in_continuous_mode (struct vpfe_resizer_device*) ; 
 int resizer_configure_in_single_shot_mode (struct vpfe_resizer_device*) ; 
 struct vpfe_device* to_vpfe_device (struct vpfe_resizer_device*) ; 

__attribute__((used)) static int resizer_do_hw_setup(struct vpfe_resizer_device *resizer)
{
	struct vpfe_device *vpfe_dev = to_vpfe_device(resizer);
	u16 ipipeif_sink = vpfe_dev->vpfe_ipipeif.input;
	u16 ipipeif_source = vpfe_dev->vpfe_ipipeif.output;
	struct resizer_params *param = &resizer->config;
	int ret = 0;

	if (resizer->resizer_a.output == RESIZER_OUTPUT_MEMORY ||
	    resizer->resizer_b.output == RESIZER_OUTPUT_MEMORY) {
		if (ipipeif_sink == IPIPEIF_INPUT_MEMORY &&
		    ipipeif_source == IPIPEIF_OUTPUT_RESIZER)
			ret = resizer_configure_in_single_shot_mode(resizer);
		else
			ret =  resizer_configure_in_continuous_mode(resizer);
		if (ret)
			return ret;
		ret = config_rsz_hw(resizer, param);
	}
	return ret;
}