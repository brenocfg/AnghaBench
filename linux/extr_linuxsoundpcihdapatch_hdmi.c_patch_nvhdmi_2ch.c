#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  formats; int /*<<< orphan*/  maxbps; int /*<<< orphan*/  rates; } ;
struct hdmi_spec {TYPE_2__ pcm_playback; } ;
struct TYPE_3__ {int /*<<< orphan*/  init; } ;
struct hda_codec {struct hdmi_spec* spec; TYPE_1__ patch_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUPPORTED_FORMATS ; 
 int /*<<< orphan*/  SUPPORTED_MAXBPS ; 
 int /*<<< orphan*/  SUPPORTED_RATES ; 
 int /*<<< orphan*/  nvhdmi_7x_init_2ch ; 
 int /*<<< orphan*/  nvhdmi_master_con_nid_7x ; 
 int /*<<< orphan*/  nvhdmi_master_pin_nid_7x ; 
 int patch_simple_hdmi (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int patch_nvhdmi_2ch(struct hda_codec *codec)
{
	struct hdmi_spec *spec;
	int err = patch_simple_hdmi(codec, nvhdmi_master_con_nid_7x,
				    nvhdmi_master_pin_nid_7x);
	if (err < 0)
		return err;

	codec->patch_ops.init = nvhdmi_7x_init_2ch;
	/* override the PCM rates, etc, as the codec doesn't give full list */
	spec = codec->spec;
	spec->pcm_playback.rates = SUPPORTED_RATES;
	spec->pcm_playback.maxbps = SUPPORTED_MAXBPS;
	spec->pcm_playback.formats = SUPPORTED_FORMATS;
	return 0;
}