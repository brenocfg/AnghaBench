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
struct snd_jack {int dummy; } ;
struct hdmi_spec_per_pin {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev_id; int /*<<< orphan*/  pin_nid; } ;
struct hdmi_eld {int monitor_present; int eld_valid; int eld_size; int /*<<< orphan*/  eld_buffer; int /*<<< orphan*/  info; } ;
struct hdmi_spec {struct hdmi_eld temp_eld; } ;
struct hda_codec {int /*<<< orphan*/  core; struct hdmi_spec* spec; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ELD_MAX_SIZE ; 
 int /*<<< orphan*/  SND_JACK_AVOUT ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct snd_jack* pin_idx_to_jack (struct hda_codec*,struct hdmi_spec_per_pin*) ; 
 int snd_hdac_acomp_get_eld (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_hdmi_parse_eld (struct hda_codec*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_jack_report (struct snd_jack*,int /*<<< orphan*/ ) ; 
 int update_eld (struct hda_codec*,struct hdmi_spec_per_pin*,struct hdmi_eld*) ; 

__attribute__((used)) static void sync_eld_via_acomp(struct hda_codec *codec,
			       struct hdmi_spec_per_pin *per_pin)
{
	struct hdmi_spec *spec = codec->spec;
	struct hdmi_eld *eld = &spec->temp_eld;
	struct snd_jack *jack = NULL;
	bool changed;
	int size;

	mutex_lock(&per_pin->lock);
	eld->monitor_present = false;
	size = snd_hdac_acomp_get_eld(&codec->core, per_pin->pin_nid,
				      per_pin->dev_id, &eld->monitor_present,
				      eld->eld_buffer, ELD_MAX_SIZE);
	if (size > 0) {
		size = min(size, ELD_MAX_SIZE);
		if (snd_hdmi_parse_eld(codec, &eld->info,
				       eld->eld_buffer, size) < 0)
			size = -EINVAL;
	}

	if (size > 0) {
		eld->eld_valid = true;
		eld->eld_size = size;
	} else {
		eld->eld_valid = false;
		eld->eld_size = 0;
	}

	/* pcm_idx >=0 before update_eld() means it is in monitor
	 * disconnected event. Jack must be fetched before update_eld()
	 */
	jack = pin_idx_to_jack(codec, per_pin);
	changed = update_eld(codec, per_pin, eld);
	if (jack == NULL)
		jack = pin_idx_to_jack(codec, per_pin);
	if (changed && jack)
		snd_jack_report(jack,
				(eld->monitor_present && eld->eld_valid) ?
				SND_JACK_AVOUT : 0);
	mutex_unlock(&per_pin->lock);
}