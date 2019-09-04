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
struct vpfe_ipipe_rgb2yuv {int dummy; } ;
struct TYPE_2__ {struct vpfe_ipipe_rgb2yuv rgb2yuv; } ;
struct vpfe_ipipe_device {TYPE_1__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct vpfe_ipipe_rgb2yuv*,struct vpfe_ipipe_rgb2yuv*,int) ; 

__attribute__((used)) static int
ipipe_get_rgb2yuv_params(struct vpfe_ipipe_device *ipipe, void *param)
{
	struct vpfe_ipipe_rgb2yuv *rgb2yuv = &ipipe->config.rgb2yuv;
	struct vpfe_ipipe_rgb2yuv *rgb2yuv_param;

	rgb2yuv_param = param;
	memcpy(rgb2yuv_param, rgb2yuv, sizeof(struct vpfe_ipipe_rgb2yuv));
	return 0;
}