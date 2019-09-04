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
struct TYPE_5__ {scalar_t__ set_gamma; } ;
struct TYPE_4__ {scalar_t__ curves; } ;
struct fbtft_par {TYPE_3__* info; TYPE_2__ fbtftops; TYPE_1__ gamma; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug_device_attr ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gamma_device_attrs ; 

void fbtft_sysfs_exit(struct fbtft_par *par)
{
	device_remove_file(par->info->dev, &debug_device_attr);
	if (par->gamma.curves && par->fbtftops.set_gamma)
		device_remove_file(par->info->dev, &gamma_device_attrs[0]);
}