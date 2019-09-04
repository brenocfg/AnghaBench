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
struct hdmi_spec {int /*<<< orphan*/  vendor_nid; } ;
struct hda_codec {int /*<<< orphan*/  core; struct hdmi_spec* spec; } ;

/* Variables and functions */
 unsigned int INTEL_EN_DP12 ; 
 int /*<<< orphan*/  INTEL_GET_VENDOR_VERB ; 
 int /*<<< orphan*/  INTEL_SET_VENDOR_VERB ; 
 unsigned int snd_hda_codec_read (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_codec_write_cache (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  snd_hdac_regmap_add_vendor_verb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_haswell_fixup_enable_dp12(struct hda_codec *codec)
{
	unsigned int vendor_param;
	struct hdmi_spec *spec = codec->spec;

	vendor_param = snd_hda_codec_read(codec, spec->vendor_nid, 0,
				INTEL_GET_VENDOR_VERB, 0);
	if (vendor_param == -1 || vendor_param & INTEL_EN_DP12)
		return;

	/* enable DP1.2 mode */
	vendor_param |= INTEL_EN_DP12;
	snd_hdac_regmap_add_vendor_verb(&codec->core, INTEL_SET_VENDOR_VERB);
	snd_hda_codec_write_cache(codec, spec->vendor_nid, 0,
				INTEL_SET_VENDOR_VERB, vendor_param);
}