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
struct hdmi_spec_per_pin {int dev_id; int /*<<< orphan*/  pin_nid; } ;
struct hdmi_spec {int use_jack_detect; int num_pins; int /*<<< orphan*/  bind_lock; } ;
struct hda_codec {int /*<<< orphan*/  jackpoll_interval; struct hdmi_spec* spec; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 scalar_t__ codec_has_acomp (struct hda_codec*) ; 
 struct hdmi_spec_per_pin* get_pin (struct hdmi_spec*,int) ; 
 int /*<<< orphan*/  hdmi_init_pin (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jack_callback ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_hda_jack_detect_enable (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_jack_detect_enable_callback (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_set_dev_select (struct hda_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int generic_hdmi_init(struct hda_codec *codec)
{
	struct hdmi_spec *spec = codec->spec;
	int pin_idx;

	mutex_lock(&spec->bind_lock);
	spec->use_jack_detect = !codec->jackpoll_interval;
	for (pin_idx = 0; pin_idx < spec->num_pins; pin_idx++) {
		struct hdmi_spec_per_pin *per_pin = get_pin(spec, pin_idx);
		hda_nid_t pin_nid = per_pin->pin_nid;
		int dev_id = per_pin->dev_id;

		snd_hda_set_dev_select(codec, pin_nid, dev_id);
		hdmi_init_pin(codec, pin_nid);
		if (codec_has_acomp(codec))
			continue;
		if (spec->use_jack_detect)
			snd_hda_jack_detect_enable(codec, pin_nid);
		else
			snd_hda_jack_detect_enable_callback(codec, pin_nid,
							    jack_callback);
	}
	mutex_unlock(&spec->bind_lock);
	return 0;
}