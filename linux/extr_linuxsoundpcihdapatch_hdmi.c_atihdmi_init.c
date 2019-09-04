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
struct hdmi_spec_per_pin {int /*<<< orphan*/  pin_nid; } ;
struct hdmi_spec {int num_pins; } ;
struct hda_codec {struct hdmi_spec* spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATI_MULTICHANNEL_MODE_SINGLE ; 
 int /*<<< orphan*/  ATI_VERB_SET_DOWNMIX_INFO ; 
 int /*<<< orphan*/  ATI_VERB_SET_MULTICHANNEL_MODE ; 
 int generic_hdmi_init (struct hda_codec*) ; 
 struct hdmi_spec_per_pin* get_pin (struct hdmi_spec*,int) ; 
 scalar_t__ has_amd_full_remap_support (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atihdmi_init(struct hda_codec *codec)
{
	struct hdmi_spec *spec = codec->spec;
	int pin_idx, err;

	err = generic_hdmi_init(codec);

	if (err)
		return err;

	for (pin_idx = 0; pin_idx < spec->num_pins; pin_idx++) {
		struct hdmi_spec_per_pin *per_pin = get_pin(spec, pin_idx);

		/* make sure downmix information in infoframe is zero */
		snd_hda_codec_write(codec, per_pin->pin_nid, 0, ATI_VERB_SET_DOWNMIX_INFO, 0);

		/* enable channel-wise remap mode if supported */
		if (has_amd_full_remap_support(codec))
			snd_hda_codec_write(codec, per_pin->pin_nid, 0,
					    ATI_VERB_SET_MULTICHANNEL_MODE,
					    ATI_MULTICHANNEL_MODE_SINGLE);
	}

	return 0;
}