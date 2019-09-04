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
struct pmac_gpio {int active_val; int inactive_val; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  do_gpio_write (struct pmac_gpio*,int) ; 

__attribute__((used)) static void write_audio_gpio(struct pmac_gpio *gp, int active)
{
	if (! gp->addr)
		return;
	active = active ? gp->active_val : gp->inactive_val;
	do_gpio_write(gp, active);
	DBG("(I) gpio %x write %d\n", gp->addr, active);
}