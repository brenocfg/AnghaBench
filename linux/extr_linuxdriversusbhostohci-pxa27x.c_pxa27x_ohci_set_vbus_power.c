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
struct regulator {int dummy; } ;
struct pxa27x_ohci {int* vbus_enabled; struct regulator** vbus; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct regulator*) ; 
 int regulator_disable (struct regulator*) ; 
 int regulator_enable (struct regulator*) ; 

__attribute__((used)) static int pxa27x_ohci_set_vbus_power(struct pxa27x_ohci *pxa_ohci,
				      unsigned int port, bool enable)
{
	struct regulator *vbus = pxa_ohci->vbus[port];
	int ret = 0;

	if (IS_ERR_OR_NULL(vbus))
		return 0;

	if (enable && !pxa_ohci->vbus_enabled[port])
		ret = regulator_enable(vbus);
	else if (!enable && pxa_ohci->vbus_enabled[port])
		ret = regulator_disable(vbus);

	if (ret < 0)
		return ret;

	pxa_ohci->vbus_enabled[port] = enable;

	return 0;
}