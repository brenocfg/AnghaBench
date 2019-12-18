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
struct rt5651_priv {int /*<<< orphan*/ * gpiod_hp_det; TYPE_1__* hp_jack; } ;
struct TYPE_2__ {int status; } ;

/* Variables and functions */
 int SND_JACK_MICROPHONE ; 

__attribute__((used)) static bool rt5651_support_button_press(struct rt5651_priv *rt5651)
{
	if (!rt5651->hp_jack)
		return false;

	/* Button press support only works with internal jack-detection */
	return (rt5651->hp_jack->status & SND_JACK_MICROPHONE) &&
		rt5651->gpiod_hp_det == NULL;
}