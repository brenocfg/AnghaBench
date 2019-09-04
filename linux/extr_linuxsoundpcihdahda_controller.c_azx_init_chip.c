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
struct azx {int driver_caps; } ;

/* Variables and functions */
 int AZX_DCAPS_CTX_WORKAROUND ; 
 int /*<<< orphan*/  RINTCNT ; 
 int /*<<< orphan*/  azx_bus (struct azx*) ; 
 int /*<<< orphan*/  azx_writew (struct azx*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ snd_hdac_bus_init_chip (int /*<<< orphan*/ ,int) ; 

void azx_init_chip(struct azx *chip, bool full_reset)
{
	if (snd_hdac_bus_init_chip(azx_bus(chip), full_reset)) {
		/* correct RINTCNT for CXT */
		if (chip->driver_caps & AZX_DCAPS_CTX_WORKAROUND)
			azx_writew(chip, RINTCNT, 0xc0);
	}
}