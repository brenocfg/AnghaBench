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
struct meson_pwm_channel {int dummy; } ;
struct TYPE_2__ {unsigned int npwm; int /*<<< orphan*/ * pwms; } ;
struct meson_pwm {TYPE_1__ chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  pwm_set_chip_data (int /*<<< orphan*/ *,struct meson_pwm_channel*) ; 

__attribute__((used)) static void meson_pwm_add_channels(struct meson_pwm *meson,
				   struct meson_pwm_channel *channels)
{
	unsigned int i;

	for (i = 0; i < meson->chip.npwm; i++)
		pwm_set_chip_data(&meson->chip.pwms[i], &channels[i]);
}