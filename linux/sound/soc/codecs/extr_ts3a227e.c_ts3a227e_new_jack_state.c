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
struct ts3a227e {int plugged; int mic_present; int /*<<< orphan*/  regmap; scalar_t__ buttons_held; } ;

/* Variables and functions */
 unsigned int EITHER_MIC_MASK ; 
 unsigned int JACK_INSERTED ; 
 int /*<<< orphan*/  KP_ENABLE ; 
 int /*<<< orphan*/  TS3A227E_REG_SETTING_2 ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ts3a227e_new_jack_state(struct ts3a227e *ts3a227e, unsigned acc_reg)
{
	bool plugged, mic_present;

	plugged = !!(acc_reg & JACK_INSERTED);
	mic_present = plugged && !!(acc_reg & EITHER_MIC_MASK);

	ts3a227e->plugged = plugged;

	if (mic_present != ts3a227e->mic_present) {
		ts3a227e->mic_present = mic_present;
		ts3a227e->buttons_held = 0;
		if (mic_present) {
			/* Enable key press detection. */
			regmap_update_bits(ts3a227e->regmap,
					   TS3A227E_REG_SETTING_2,
					   KP_ENABLE, KP_ENABLE);
		}
	}
}