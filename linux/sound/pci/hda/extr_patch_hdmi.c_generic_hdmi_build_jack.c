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
struct hdmi_spec_per_pin {int /*<<< orphan*/  pin_nid; } ;
struct hdmi_spec {TYPE_1__* pcm_rec; scalar_t__ dyn_pcm_assign; } ;
struct hda_jack_tbl {int /*<<< orphan*/  jack; } ;
struct hda_codec {struct hdmi_spec* spec; } ;
typedef  int /*<<< orphan*/  hdmi_str ;
struct TYPE_4__ {int device; } ;
struct TYPE_3__ {int /*<<< orphan*/  jack; } ;

/* Variables and functions */
 int add_hdmi_jack_kctl (struct hda_codec*,struct hdmi_spec*,int,char*) ; 
 TYPE_2__* get_pcm_rec (struct hdmi_spec*,int) ; 
 struct hdmi_spec_per_pin* get_pin (struct hdmi_spec*,int) ; 
 int /*<<< orphan*/  is_jack_detectable (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int snd_hda_jack_add_kctl (struct hda_codec*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct hda_jack_tbl* snd_hda_jack_tbl_get (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncat (char*,char*,int) ; 

__attribute__((used)) static int generic_hdmi_build_jack(struct hda_codec *codec, int pcm_idx)
{
	char hdmi_str[32] = "HDMI/DP";
	struct hdmi_spec *spec = codec->spec;
	struct hdmi_spec_per_pin *per_pin;
	struct hda_jack_tbl *jack;
	int pcmdev = get_pcm_rec(spec, pcm_idx)->device;
	bool phantom_jack;
	int ret;

	if (pcmdev > 0)
		sprintf(hdmi_str + strlen(hdmi_str), ",pcm=%d", pcmdev);

	if (spec->dyn_pcm_assign)
		return add_hdmi_jack_kctl(codec, spec, pcm_idx, hdmi_str);

	/* for !dyn_pcm_assign, we still use hda_jack for compatibility */
	/* if !dyn_pcm_assign, it must be non-MST mode.
	 * This means pcms and pins are statically mapped.
	 * And pcm_idx is pin_idx.
	 */
	per_pin = get_pin(spec, pcm_idx);
	phantom_jack = !is_jack_detectable(codec, per_pin->pin_nid);
	if (phantom_jack)
		strncat(hdmi_str, " Phantom",
			sizeof(hdmi_str) - strlen(hdmi_str) - 1);
	ret = snd_hda_jack_add_kctl(codec, per_pin->pin_nid, hdmi_str,
				    phantom_jack, 0, NULL);
	if (ret < 0)
		return ret;
	jack = snd_hda_jack_tbl_get(codec, per_pin->pin_nid);
	if (jack == NULL)
		return 0;
	/* assign jack->jack to pcm_rec[].jack to
	 * align with dyn_pcm_assign mode
	 */
	spec->pcm_rec[pcm_idx].jack = jack->jack;
	return 0;
}