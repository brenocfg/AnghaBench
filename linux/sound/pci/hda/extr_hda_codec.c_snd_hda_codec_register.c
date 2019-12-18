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
struct hda_codec {int registered; } ;

/* Variables and functions */
 int /*<<< orphan*/  codec_display_power (struct hda_codec*,int) ; 
 scalar_t__ device_is_registered (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hda_codec_dev (struct hda_codec*) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_power_down (struct hda_codec*) ; 

void snd_hda_codec_register(struct hda_codec *codec)
{
	if (codec->registered)
		return;
	if (device_is_registered(hda_codec_dev(codec))) {
		codec_display_power(codec, true);
		pm_runtime_enable(hda_codec_dev(codec));
		/* it was powered up in snd_hda_codec_new(), now all done */
		snd_hda_power_down(codec);
		codec->registered = 1;
	}
}