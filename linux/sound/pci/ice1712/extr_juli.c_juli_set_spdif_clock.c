#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int (* get_data ) (struct snd_ice1712*) ;int /*<<< orphan*/  (* set_data ) (struct snd_ice1712*,unsigned int) ;} ;
struct snd_ice1712 {TYPE_1__ gpio; } ;

/* Variables and functions */
 unsigned int GPIO_FREQ_48KHZ ; 
 unsigned int GPIO_MULTI_1X ; 
 unsigned int GPIO_RATE_MASK ; 
 unsigned int stub1 (struct snd_ice1712*) ; 
 int /*<<< orphan*/  stub2 (struct snd_ice1712*,unsigned int) ; 

__attribute__((used)) static int juli_set_spdif_clock(struct snd_ice1712 *ice, int type)
{
	unsigned int old;
	old = ice->gpio.get_data(ice);
	/* external clock (= 0), multiply 1x, 48kHz */
	ice->gpio.set_data(ice, (old & ~GPIO_RATE_MASK) | GPIO_MULTI_1X |
			GPIO_FREQ_48KHZ);
	return 0;
}