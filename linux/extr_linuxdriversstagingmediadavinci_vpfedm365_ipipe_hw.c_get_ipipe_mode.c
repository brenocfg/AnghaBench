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
typedef  scalar_t__ u16 ;
struct vpfe_ipipe_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ input; } ;
struct vpfe_device {TYPE_1__ vpfe_ipipeif; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IPIPEIF_INPUT_ISIF ; 
 scalar_t__ IPIPEIF_INPUT_MEMORY ; 
 int IPIPE_MODE_CONTINUOUS ; 
 int IPIPE_MODE_SINGLE_SHOT ; 
 struct vpfe_device* to_vpfe_device (struct vpfe_ipipe_device*) ; 

__attribute__((used)) static int get_ipipe_mode(struct vpfe_ipipe_device *ipipe)
{
	struct vpfe_device *vpfe_dev = to_vpfe_device(ipipe);
	u16 ipipeif_sink = vpfe_dev->vpfe_ipipeif.input;

	if (ipipeif_sink == IPIPEIF_INPUT_MEMORY)
		return IPIPE_MODE_SINGLE_SHOT;
	if (ipipeif_sink == IPIPEIF_INPUT_ISIF)
		return IPIPE_MODE_CONTINUOUS;

	return -EINVAL;
}