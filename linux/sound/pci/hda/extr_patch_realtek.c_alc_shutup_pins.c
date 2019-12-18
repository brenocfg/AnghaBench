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
struct TYPE_2__ {int vendor_id; } ;
struct hda_codec {TYPE_1__ core; struct alc_spec* spec; } ;
struct alc_spec {int /*<<< orphan*/  no_shutup_pins; } ;

/* Variables and functions */
 int /*<<< orphan*/  alc_headset_mic_no_shutup (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_shutup_pins (struct hda_codec*) ; 

__attribute__((used)) static void alc_shutup_pins(struct hda_codec *codec)
{
	struct alc_spec *spec = codec->spec;

	switch (codec->core.vendor_id) {
	case 0x10ec0286:
	case 0x10ec0288:
	case 0x10ec0298:
		alc_headset_mic_no_shutup(codec);
		break;
	default:
		if (!spec->no_shutup_pins)
			snd_hda_shutup_pins(codec);
		break;
	}
}