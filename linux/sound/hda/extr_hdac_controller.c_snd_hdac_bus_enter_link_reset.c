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
struct hdac_bus {int dummy; } ;

/* Variables and functions */
 int AZX_GCTL_RESET ; 
 int /*<<< orphan*/  GCTL ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int snd_hdac_chip_readb (struct hdac_bus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hdac_chip_updatel (struct hdac_bus*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

void snd_hdac_bus_enter_link_reset(struct hdac_bus *bus)
{
	unsigned long timeout;

	/* reset controller */
	snd_hdac_chip_updatel(bus, GCTL, AZX_GCTL_RESET, 0);

	timeout = jiffies + msecs_to_jiffies(100);
	while ((snd_hdac_chip_readb(bus, GCTL) & AZX_GCTL_RESET) &&
	       time_before(jiffies, timeout))
		usleep_range(500, 1000);
}