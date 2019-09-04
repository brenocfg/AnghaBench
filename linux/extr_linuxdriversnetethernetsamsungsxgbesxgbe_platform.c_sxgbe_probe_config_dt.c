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
struct sxgbe_plat_data {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int ENOSYS ; 

__attribute__((used)) static int sxgbe_probe_config_dt(struct platform_device *pdev,
				 struct sxgbe_plat_data *plat,
				 const char **mac)
{
	return -ENOSYS;
}