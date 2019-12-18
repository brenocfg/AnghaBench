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
struct azx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  azx_bus (struct azx*) ; 
 int /*<<< orphan*/  snd_hdac_bus_stop_chip (int /*<<< orphan*/ ) ; 

void azx_stop_chip(struct azx *chip)
{
	snd_hdac_bus_stop_chip(azx_bus(chip));
}