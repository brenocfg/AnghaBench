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
struct hdmi_spec {unsigned int num_pins; } ;
struct hda_pcm {int pcm_type; } ;
struct hda_codec {struct hdmi_spec* spec; } ;

/* Variables and functions */
 struct hda_pcm* get_pcm_rec (struct hdmi_spec*,unsigned int) ; 

__attribute__((used)) static struct hda_pcm *hda_find_pcm_by_type(struct hda_codec *codec, int type)
{
	struct hdmi_spec *spec = codec->spec;
	unsigned int i;

	for (i = 0; i < spec->num_pins; i++) {
		struct hda_pcm *pcm = get_pcm_rec(spec, i);

		if (pcm->pcm_type == type)
			return pcm;
	}

	return NULL;
}