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
struct hda_codec {struct cs_spec* spec; } ;
struct cs_spec {scalar_t__ vendor_nid; scalar_t__ gpio_data; scalar_t__ gpio_dir; scalar_t__ gpio_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_SET_GPIO_DATA ; 
 int /*<<< orphan*/  AC_VERB_SET_GPIO_DIRECTION ; 
 int /*<<< orphan*/  AC_VERB_SET_GPIO_MASK ; 
 scalar_t__ CS4210_VENDOR_NID ; 
 int /*<<< orphan*/  cs4210_pinmux_init (struct hda_codec*) ; 
 int /*<<< orphan*/  cs4210_spdif_automute (struct hda_codec*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cs421x_coef_init_verbs ; 
 int /*<<< orphan*/  cs421x_coef_init_verbs_A1_silicon_fixes ; 
 int /*<<< orphan*/  init_input_coef (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  snd_hda_gen_init (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_sequence_write (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs421x_init(struct hda_codec *codec)
{
	struct cs_spec *spec = codec->spec;

	if (spec->vendor_nid == CS4210_VENDOR_NID) {
		snd_hda_sequence_write(codec, cs421x_coef_init_verbs);
		snd_hda_sequence_write(codec, cs421x_coef_init_verbs_A1_silicon_fixes);
		cs4210_pinmux_init(codec);
	}

	snd_hda_gen_init(codec);

	if (spec->gpio_mask) {
		snd_hda_codec_write(codec, 0x01, 0, AC_VERB_SET_GPIO_MASK,
				    spec->gpio_mask);
		snd_hda_codec_write(codec, 0x01, 0, AC_VERB_SET_GPIO_DIRECTION,
				    spec->gpio_dir);
		snd_hda_codec_write(codec, 0x01, 0, AC_VERB_SET_GPIO_DATA,
				    spec->gpio_data);
	}

	init_input_coef(codec);

	cs4210_spdif_automute(codec, NULL);

	return 0;
}