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
struct pmac_gpio {int active_state; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int do_gpio_read (struct pmac_gpio*) ; 

__attribute__((used)) static int read_audio_gpio(struct pmac_gpio *gp)
{
	int ret;
	if (! gp->addr)
		return 0;
	ret = do_gpio_read(gp);
	ret = (ret & 0x02) !=0;
	return ret == gp->active_state;
}