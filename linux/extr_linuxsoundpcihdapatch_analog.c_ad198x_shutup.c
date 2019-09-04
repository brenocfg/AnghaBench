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

/* Variables and functions */
 int /*<<< orphan*/  ad198x_power_eapd (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_shutup_pins (struct hda_codec*) ; 

__attribute__((used)) static void ad198x_shutup(struct hda_codec *codec)
{
	snd_hda_shutup_pins(codec);
	ad198x_power_eapd(codec);
}