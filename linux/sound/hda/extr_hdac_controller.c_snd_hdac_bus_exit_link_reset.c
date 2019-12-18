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
 int /*<<< orphan*/  AZX_GCTL_RESET ; 
 int /*<<< orphan*/  GCTL ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  snd_hdac_chip_readb (struct hdac_bus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hdac_chip_updateb (struct hdac_bus*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

void snd_hdac_bus_exit_link_reset(struct hdac_bus *bus)
{
	unsigned long timeout;

	snd_hdac_chip_updateb(bus, GCTL, AZX_GCTL_RESET, AZX_GCTL_RESET);

	timeout = jiffies + msecs_to_jiffies(100);
	while (!snd_hdac_chip_readb(bus, GCTL) && time_before(jiffies, timeout))
		usleep_range(500, 1000);
}