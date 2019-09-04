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
struct hdac_bus {int dummy; } ;
struct azx {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* link_power ) (struct azx*,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 struct azx* bus_to_azx (struct hdac_bus*) ; 
 int stub1 (struct azx*,int) ; 

__attribute__((used)) static int azx_link_power(struct hdac_bus *bus, bool enable)
{
	struct azx *chip = bus_to_azx(bus);

	if (chip->ops->link_power)
		return chip->ops->link_power(chip, enable);
	else
		return -EINVAL;
}