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
struct TYPE_2__ {int /*<<< orphan*/  afg; } ;
struct hda_codec {TYPE_1__ core; struct alc_spec* spec; } ;
struct alc_spec {scalar_t__ gpio_write_delay; int /*<<< orphan*/  gpio_dir; int /*<<< orphan*/  gpio_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_SET_GPIO_DIRECTION ; 
 int /*<<< orphan*/  AC_VERB_SET_GPIO_MASK ; 
 int /*<<< orphan*/  alc_write_gpio_data (struct hda_codec*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void alc_write_gpio(struct hda_codec *codec)
{
	struct alc_spec *spec = codec->spec;

	if (!spec->gpio_mask)
		return;

	snd_hda_codec_write(codec, codec->core.afg, 0,
			    AC_VERB_SET_GPIO_MASK, spec->gpio_mask);
	snd_hda_codec_write(codec, codec->core.afg, 0,
			    AC_VERB_SET_GPIO_DIRECTION, spec->gpio_dir);
	if (spec->gpio_write_delay)
		msleep(1);
	alc_write_gpio_data(codec);
}