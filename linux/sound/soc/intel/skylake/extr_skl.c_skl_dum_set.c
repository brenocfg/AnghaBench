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
struct hdac_bus {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AZX_GCTL_RESET ; 
 int /*<<< orphan*/  AZX_VS_EM2_DUM ; 
 int /*<<< orphan*/  GCTL ; 
 int /*<<< orphan*/  VS_EM2 ; 
 int /*<<< orphan*/  skl_enable_miscbdcge (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_hdac_bus_exit_link_reset (struct hdac_bus*) ; 
 int snd_hdac_chip_readb (struct hdac_bus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hdac_chip_updatel (struct hdac_bus*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void skl_dum_set(struct hdac_bus *bus)
{
	/* For the DUM bit to be set, CRST needs to be out of reset state */
	if (!(snd_hdac_chip_readb(bus, GCTL) & AZX_GCTL_RESET)) {
		skl_enable_miscbdcge(bus->dev, false);
		snd_hdac_bus_exit_link_reset(bus);
		skl_enable_miscbdcge(bus->dev, true);
	}

	snd_hdac_chip_updatel(bus, VS_EM2, AZX_VS_EM2_DUM, AZX_VS_EM2_DUM);
}