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
struct hda_fixup {int dummy; } ;
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int HDA_FIXUP_ACT_PROBE ; 
 int /*<<< orphan*/  snd_hda_jack_set_gating_jack (struct hda_codec*,int,int) ; 

__attribute__((used)) static void cxt_fixup_hp_gate_mic_jack(struct hda_codec *codec,
				       const struct hda_fixup *fix,
				       int action)
{
	/* the mic pin (0x19) doesn't give an unsolicited event;
	 * probe the mic pin together with the headphone pin (0x16)
	 */
	if (action == HDA_FIXUP_ACT_PROBE)
		snd_hda_jack_set_gating_jack(codec, 0x19, 0x16);
}