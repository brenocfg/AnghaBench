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
struct snd_pcm_substream {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  POODLE_LOCOMO_GPIO_MUTE_L ; 
 int /*<<< orphan*/  POODLE_LOCOMO_GPIO_MUTE_R ; 
 int /*<<< orphan*/  locomo_gpio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ poodle_locomo_device ; 

__attribute__((used)) static void poodle_shutdown(struct snd_pcm_substream *substream)
{
	/* set = unmute headphone */
	locomo_gpio_write(&poodle_locomo_device.dev,
		POODLE_LOCOMO_GPIO_MUTE_L, 1);
	locomo_gpio_write(&poodle_locomo_device.dev,
		POODLE_LOCOMO_GPIO_MUTE_R, 1);
}