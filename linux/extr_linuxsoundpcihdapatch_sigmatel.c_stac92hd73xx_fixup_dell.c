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
struct sigmatel_spec {scalar_t__ eapd_switch; } ;
struct hda_codec {struct sigmatel_spec* spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  dell_m6_pin_configs ; 
 int /*<<< orphan*/  snd_hda_apply_pincfgs (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stac92hd73xx_fixup_dell(struct hda_codec *codec)
{
	struct sigmatel_spec *spec = codec->spec;

	snd_hda_apply_pincfgs(codec, dell_m6_pin_configs);
	spec->eapd_switch = 0;
}