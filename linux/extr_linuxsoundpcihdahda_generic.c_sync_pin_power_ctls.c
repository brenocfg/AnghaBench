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
struct hda_codec {int dummy; } ;
typedef  scalar_t__ hda_nid_t ;

/* Variables and functions */
 scalar_t__ is_jack_detectable (struct hda_codec*,scalar_t__ const) ; 
 int /*<<< orphan*/  set_pin_power_jack (struct hda_codec*,scalar_t__ const,int) ; 

__attribute__((used)) static void sync_pin_power_ctls(struct hda_codec *codec, int num_pins,
				const hda_nid_t *pins)
{
	int i;

	for (i = 0; i < num_pins && pins[i]; i++)
		if (is_jack_detectable(codec, pins[i]))
			set_pin_power_jack(codec, pins[i], -1);
}