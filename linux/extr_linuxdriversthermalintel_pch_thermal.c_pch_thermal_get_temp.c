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
struct thermal_zone_device {struct pch_thermal_device* devdata; } ;
struct pch_thermal_device {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* get_temp ) (struct pch_thermal_device*,int*) ;} ;

/* Variables and functions */
 int stub1 (struct pch_thermal_device*,int*) ; 

__attribute__((used)) static int pch_thermal_get_temp(struct thermal_zone_device *tzd, int *temp)
{
	struct pch_thermal_device *ptd = tzd->devdata;

	return	ptd->ops->get_temp(ptd, temp);
}