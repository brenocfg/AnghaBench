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
typedef  int /*<<< orphan*/  hda_jack_callback_fn ;

/* Variables and functions */
 scalar_t__ is_jack_detectable (struct hda_codec*,scalar_t__ const) ; 
 int /*<<< orphan*/  pin_power_down_callback ; 
 int /*<<< orphan*/  pin_power_up_callback ; 
 int /*<<< orphan*/  set_path_power (struct hda_codec*,scalar_t__ const,int,int) ; 
 int /*<<< orphan*/  snd_hda_jack_detect_enable_callback (struct hda_codec*,scalar_t__ const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_pin_power_ctls(struct hda_codec *codec, int num_pins,
			       const hda_nid_t *pins, bool on)
{
	int i;
	hda_jack_callback_fn cb =
		on ? pin_power_up_callback : pin_power_down_callback;

	for (i = 0; i < num_pins && pins[i]; i++) {
		if (is_jack_detectable(codec, pins[i]))
			snd_hda_jack_detect_enable_callback(codec, pins[i], cb);
		else
			set_path_power(codec, pins[i], true, -1);
	}
}