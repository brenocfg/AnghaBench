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
struct hdmi_spec {int /*<<< orphan*/  pcm_lock; } ;
struct hda_codec {struct hdmi_spec* spec; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  get_pin (struct hdmi_spec*,int) ; 
 scalar_t__ hdmi_present_sense (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pin_id_to_pin_index (struct hda_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_hda_jack_report_sync (struct hda_codec*) ; 

__attribute__((used)) static void check_presence_and_report(struct hda_codec *codec, hda_nid_t nid,
				      int dev_id)
{
	struct hdmi_spec *spec = codec->spec;
	int pin_idx = pin_id_to_pin_index(codec, nid, dev_id);

	if (pin_idx < 0)
		return;
	mutex_lock(&spec->pcm_lock);
	if (hdmi_present_sense(get_pin(spec, pin_idx), 1))
		snd_hda_jack_report_sync(codec);
	mutex_unlock(&spec->pcm_lock);
}