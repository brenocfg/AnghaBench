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
struct hda_codec {TYPE_1__ core; } ;
typedef  enum r3di_dsp_status { ____Placeholder_r3di_dsp_status } r3di_dsp_status ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_GET_GPIO_DATA ; 
 int /*<<< orphan*/  AC_VERB_SET_GPIO_DATA ; 
#define  R3DI_DSP_DOWNLOADED 129 
#define  R3DI_DSP_DOWNLOADING 128 
 int R3DI_GPIO_DSP_DOWNLOADED ; 
 int R3DI_GPIO_DSP_DOWNLOADING ; 
 unsigned int snd_hda_codec_read (struct hda_codec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void r3di_gpio_dsp_status_set(struct hda_codec *codec,
		enum r3di_dsp_status dsp_status)
{
	unsigned int cur_gpio;

	/* Get the current GPIO Data setup */
	cur_gpio = snd_hda_codec_read(codec, 0x01, 0, AC_VERB_GET_GPIO_DATA, 0);

	switch (dsp_status) {
	case R3DI_DSP_DOWNLOADING:
		cur_gpio |= (1 << R3DI_GPIO_DSP_DOWNLOADING);
		snd_hda_codec_write(codec, codec->core.afg, 0,
				AC_VERB_SET_GPIO_DATA, cur_gpio);
		break;
	case R3DI_DSP_DOWNLOADED:
		/* Set DOWNLOADING bit to 0. */
		cur_gpio &= ~(1 << R3DI_GPIO_DSP_DOWNLOADING);

		snd_hda_codec_write(codec, codec->core.afg, 0,
				AC_VERB_SET_GPIO_DATA, cur_gpio);

		cur_gpio |= (1 << R3DI_GPIO_DSP_DOWNLOADED);
		break;
	}

	snd_hda_codec_write(codec, codec->core.afg, 0,
			    AC_VERB_SET_GPIO_DATA, cur_gpio);
}