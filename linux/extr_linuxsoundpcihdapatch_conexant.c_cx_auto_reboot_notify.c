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
struct TYPE_2__ {int vendor_id; int /*<<< orphan*/  afg; } ;
struct hda_codec {TYPE_1__ core; struct conexant_spec* spec; } ;
struct conexant_spec {int /*<<< orphan*/  eapds; int /*<<< orphan*/  num_eapds; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_PWRST_D3 ; 
 int /*<<< orphan*/  AC_VERB_SET_POWER_STATE ; 
 int /*<<< orphan*/  cx_auto_turn_eapd (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  snd_hda_codec_set_power_to_all (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cx_auto_reboot_notify(struct hda_codec *codec)
{
	struct conexant_spec *spec = codec->spec;

	switch (codec->core.vendor_id) {
	case 0x14f12008: /* CX8200 */
	case 0x14f150f2: /* CX20722 */
	case 0x14f150f4: /* CX20724 */
		break;
	default:
		return;
	}

	/* Turn the problematic codec into D3 to avoid spurious noises
	   from the internal speaker during (and after) reboot */
	cx_auto_turn_eapd(codec, spec->num_eapds, spec->eapds, false);

	snd_hda_codec_set_power_to_all(codec, codec->core.afg, AC_PWRST_D3);
	snd_hda_codec_write(codec, codec->core.afg, 0,
			    AC_VERB_SET_POWER_STATE, AC_PWRST_D3);
	msleep(10);
}