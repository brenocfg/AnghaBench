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
struct vpfe_ipipe_rgb2rgb {int dummy; } ;
struct TYPE_2__ {struct vpfe_ipipe_rgb2rgb rgb2rgb2; struct vpfe_ipipe_rgb2rgb rgb2rgb1; } ;
struct vpfe_ipipe_device {TYPE_1__ config; } ;

/* Variables and functions */
 unsigned int IPIPE_RGB2RGB_2 ; 
 int /*<<< orphan*/  memcpy (struct vpfe_ipipe_rgb2rgb*,struct vpfe_ipipe_rgb2rgb*,int) ; 

__attribute__((used)) static int ipipe_get_rgb2rgb_params(struct vpfe_ipipe_device *ipipe,
			      unsigned int id, void *param)
{
	struct vpfe_ipipe_rgb2rgb *rgb2rgb = &ipipe->config.rgb2rgb1;
	struct vpfe_ipipe_rgb2rgb *rgb2rgb_param;

	rgb2rgb_param = param;

	if (id == IPIPE_RGB2RGB_2)
		rgb2rgb = &ipipe->config.rgb2rgb2;

	memcpy(rgb2rgb_param, rgb2rgb, sizeof(struct vpfe_ipipe_rgb2rgb));

	return 0;
}