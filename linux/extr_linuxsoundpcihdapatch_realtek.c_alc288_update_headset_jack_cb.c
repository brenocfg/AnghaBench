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
struct hda_jack_callback {int dummy; } ;
struct hda_codec {struct alc_spec* spec; } ;
struct TYPE_2__ {int /*<<< orphan*/  hp_jack_present; } ;
struct alc_spec {TYPE_1__ gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  alc_update_gpio_data (struct hda_codec*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alc_update_headset_jack_cb (struct hda_codec*,struct hda_jack_callback*) ; 

__attribute__((used)) static void alc288_update_headset_jack_cb(struct hda_codec *codec,
				       struct hda_jack_callback *jack)
{
	struct alc_spec *spec = codec->spec;

	alc_update_headset_jack_cb(codec, jack);
	/* Headset Mic enable or disable, only for Dell Dino */
	alc_update_gpio_data(codec, 0x40, spec->gen.hp_jack_present);
}