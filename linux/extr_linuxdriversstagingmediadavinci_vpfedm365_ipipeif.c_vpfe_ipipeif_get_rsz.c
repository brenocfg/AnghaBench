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
struct TYPE_2__ {int rsz; } ;
struct vpfe_ipipeif_device {TYPE_1__ config; } ;
struct vpfe_device {struct vpfe_ipipeif_device vpfe_ipipeif; } ;

/* Variables and functions */

int vpfe_ipipeif_get_rsz(struct vpfe_device *vpfe_dev)
{
	struct vpfe_ipipeif_device *ipipeif = &vpfe_dev->vpfe_ipipeif;

	return ipipeif->config.rsz;
}