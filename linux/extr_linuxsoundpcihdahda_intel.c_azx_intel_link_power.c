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
struct azx {int dummy; } ;

/* Variables and functions */
 struct hdac_bus* azx_bus (struct azx*) ; 
 int snd_hdac_display_power (struct hdac_bus*,int) ; 

__attribute__((used)) static int azx_intel_link_power(struct azx *chip, bool enable)
{
	struct hdac_bus *bus = azx_bus(chip);

	return snd_hdac_display_power(bus, enable);
}