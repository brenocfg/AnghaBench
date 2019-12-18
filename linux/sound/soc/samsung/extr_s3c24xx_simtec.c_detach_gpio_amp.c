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
struct s3c24xx_audio_simtec_pdata {scalar_t__* amp_gain; scalar_t__ amp_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_free (scalar_t__) ; 

__attribute__((used)) static void detach_gpio_amp(struct s3c24xx_audio_simtec_pdata *pd)
{
	if (pd->amp_gain[0] > 0) {
		gpio_free(pd->amp_gain[0]);
		gpio_free(pd->amp_gain[1]);
	}

	if (pd->amp_gpio > 0)
		gpio_free(pd->amp_gpio);
}