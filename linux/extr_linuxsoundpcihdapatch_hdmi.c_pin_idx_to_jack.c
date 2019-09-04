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
struct snd_jack {int dummy; } ;
struct hdmi_spec_per_pin {size_t pcm_idx; int /*<<< orphan*/  pin_nid; } ;
struct hdmi_spec {scalar_t__ dyn_pcm_assign; TYPE_1__* pcm_rec; } ;
struct hda_jack_tbl {struct snd_jack* jack; } ;
struct hda_codec {struct hdmi_spec* spec; } ;
struct TYPE_2__ {struct snd_jack* jack; } ;

/* Variables and functions */
 struct hda_jack_tbl* snd_hda_jack_tbl_get (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct snd_jack *pin_idx_to_jack(struct hda_codec *codec,
				 struct hdmi_spec_per_pin *per_pin)
{
	struct hdmi_spec *spec = codec->spec;
	struct snd_jack *jack = NULL;
	struct hda_jack_tbl *jack_tbl;

	/* if !dyn_pcm_assign, get jack from hda_jack_tbl
	 * in !dyn_pcm_assign case, spec->pcm_rec[].jack is not
	 * NULL even after snd_hda_jack_tbl_clear() is called to
	 * free snd_jack. This may cause access invalid memory
	 * when calling snd_jack_report
	 */
	if (per_pin->pcm_idx >= 0 && spec->dyn_pcm_assign)
		jack = spec->pcm_rec[per_pin->pcm_idx].jack;
	else if (!spec->dyn_pcm_assign) {
		/*
		 * jack tbl doesn't support DP MST
		 * DP MST will use dyn_pcm_assign,
		 * so DP MST will never come here
		 */
		jack_tbl = snd_hda_jack_tbl_get(codec, per_pin->pin_nid);
		if (jack_tbl)
			jack = jack_tbl->jack;
	}
	return jack;
}