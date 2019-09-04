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
struct vpfe_ipipe_yuv422_conv {int dummy; } ;
struct TYPE_2__ {struct vpfe_ipipe_yuv422_conv yuv422_conv; } ;
struct vpfe_ipipe_device {TYPE_1__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct vpfe_ipipe_yuv422_conv*,struct vpfe_ipipe_yuv422_conv*,int) ; 

__attribute__((used)) static int
ipipe_get_yuv422_conv_params(struct vpfe_ipipe_device *ipipe, void *param)
{
	struct vpfe_ipipe_yuv422_conv *yuv422_conv = &ipipe->config.yuv422_conv;
	struct vpfe_ipipe_yuv422_conv *yuv422_conv_param;

	yuv422_conv_param = param;
	memcpy(yuv422_conv_param, yuv422_conv,
	       sizeof(struct vpfe_ipipe_yuv422_conv));

	return 0;
}