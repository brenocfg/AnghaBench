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
 int /*<<< orphan*/  alc269_fixup_hp_mute_led_micx (struct hda_codec*,struct hda_fixup const*,int,int) ; 

__attribute__((used)) static void alc269_fixup_hp_mute_led_mic2(struct hda_codec *codec,
				const struct hda_fixup *fix, int action)
{
	alc269_fixup_hp_mute_led_micx(codec, fix, action, 0x19);
}