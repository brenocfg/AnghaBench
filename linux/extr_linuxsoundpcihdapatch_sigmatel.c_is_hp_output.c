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
 scalar_t__ AC_JACK_HP_OUT ; 
 scalar_t__ AC_JACK_LINE_OUT ; 
 scalar_t__ AC_JACK_PORT_NONE ; 
 scalar_t__ get_defcfg_connect (unsigned int) ; 
 scalar_t__ get_defcfg_device (unsigned int) ; 
 unsigned int snd_hda_codec_get_pincfg (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_hp_output(struct hda_codec *codec, hda_nid_t pin)
{
	unsigned int pin_cfg = snd_hda_codec_get_pincfg(codec, pin);

	/* count line-out, too, as BIOS sets often so */
	return get_defcfg_connect(pin_cfg) != AC_JACK_PORT_NONE &&
		(get_defcfg_device(pin_cfg) == AC_JACK_LINE_OUT ||
		 get_defcfg_device(pin_cfg) == AC_JACK_HP_OUT);
}