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
struct hdmi_spec_per_pin {TYPE_2__* pcm; } ;
struct hdmi_spec {int num_pins; } ;
struct hda_pcm_stream {int dummy; } ;
struct hda_codec {struct hdmi_spec* spec; } ;
struct TYPE_4__ {TYPE_1__* pcm; } ;
struct TYPE_3__ {struct hda_pcm_stream* stream; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*,struct hda_pcm_stream*) ; 
 struct hdmi_spec_per_pin* get_pin (struct hdmi_spec*,int) ; 

__attribute__((used)) static int hinfo_to_pin_index(struct hda_codec *codec,
			      struct hda_pcm_stream *hinfo)
{
	struct hdmi_spec *spec = codec->spec;
	struct hdmi_spec_per_pin *per_pin;
	int pin_idx;

	for (pin_idx = 0; pin_idx < spec->num_pins; pin_idx++) {
		per_pin = get_pin(spec, pin_idx);
		if (per_pin->pcm &&
			per_pin->pcm->pcm->stream == hinfo)
			return pin_idx;
	}

	codec_dbg(codec, "HDMI: hinfo %p not registered\n", hinfo);
	return -EINVAL;
}