#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vpfe_ipipe_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPIPE_RGB2RGB_2 ; 
 int ipipe_get_rgb2rgb_params (struct vpfe_ipipe_device*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int
ipipe_get_rgb2rgb_2_params(struct vpfe_ipipe_device *ipipe, void *param)
{
	return ipipe_get_rgb2rgb_params(ipipe, IPIPE_RGB2RGB_2, param);
}