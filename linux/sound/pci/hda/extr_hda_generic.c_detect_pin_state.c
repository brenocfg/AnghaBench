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
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 scalar_t__ HDA_JACK_NOT_PRESENT ; 
 int /*<<< orphan*/  is_jack_detectable (struct hda_codec*,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_hda_jack_detect_state (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool detect_pin_state(struct hda_codec *codec, hda_nid_t pin)
{
	if (!is_jack_detectable(codec, pin))
		return true;
	return snd_hda_jack_detect_state(codec, pin) != HDA_JACK_NOT_PRESENT;
}