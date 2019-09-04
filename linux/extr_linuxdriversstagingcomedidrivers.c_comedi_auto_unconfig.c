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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_release_hardware_device (struct device*) ; 

void comedi_auto_unconfig(struct device *hardware_device)
{
	if (!hardware_device)
		return;
	comedi_release_hardware_device(hardware_device);
}