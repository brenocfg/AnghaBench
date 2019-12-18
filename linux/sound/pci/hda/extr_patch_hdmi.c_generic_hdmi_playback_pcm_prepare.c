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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  channels; int /*<<< orphan*/  rate; } ;
struct hdmi_spec_per_pin {int setup; int /*<<< orphan*/  lock; int /*<<< orphan*/  channels; int /*<<< orphan*/  dev_id; int /*<<< orphan*/  pin_nid; } ;
struct TYPE_4__ {int (* setup_stream ) (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ;} ;
struct hdmi_spec {int /*<<< orphan*/  pcm_lock; TYPE_2__ ops; scalar_t__ dyn_pin_out; scalar_t__ dyn_pcm_assign; } ;
struct hda_pcm_stream {int /*<<< orphan*/  nid; } ;
struct hda_codec {TYPE_1__* bus; int /*<<< orphan*/  core; struct hdmi_spec* spec; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;
struct TYPE_3__ {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_GET_PIN_WIDGET_CONTROL ; 
 int /*<<< orphan*/  AC_VERB_SET_PIN_WIDGET_CONTROL ; 
 int /*<<< orphan*/  AC_VERB_SET_STRIPE_CONTROL ; 
 int AC_WCAP_STRIPE ; 
 int EINVAL ; 
 int PIN_OUT ; 
 int check_non_pcm_per_cvt (struct hda_codec*,int /*<<< orphan*/ ) ; 
 scalar_t__ codec_has_acomp (struct hda_codec*) ; 
 struct hdmi_spec_per_pin* get_pin (struct hdmi_spec*,int) ; 
 int get_wcaps (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_setup_audio_infoframe (struct hda_codec*,struct hdmi_spec_per_pin*,int) ; 
 int hinfo_to_pin_index (struct hda_codec*,struct hda_pcm_stream*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pin_cvt_fixup (struct hda_codec*,struct hdmi_spec_per_pin*,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int snd_hda_codec_read (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_codec_setup_stream (struct hda_codec*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int snd_hdac_get_stream_stripe_ctl (int /*<<< orphan*/ *,struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_hdac_sync_audio_rate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int generic_hdmi_playback_pcm_prepare(struct hda_pcm_stream *hinfo,
					   struct hda_codec *codec,
					   unsigned int stream_tag,
					   unsigned int format,
					   struct snd_pcm_substream *substream)
{
	hda_nid_t cvt_nid = hinfo->nid;
	struct hdmi_spec *spec = codec->spec;
	int pin_idx;
	struct hdmi_spec_per_pin *per_pin;
	hda_nid_t pin_nid;
	struct snd_pcm_runtime *runtime = substream->runtime;
	bool non_pcm;
	int pinctl, stripe;
	int err = 0;

	mutex_lock(&spec->pcm_lock);
	pin_idx = hinfo_to_pin_index(codec, hinfo);
	if (spec->dyn_pcm_assign && pin_idx < 0) {
		/* when dyn_pcm_assign and pcm is not bound to a pin
		 * skip pin setup and return 0 to make audio playback
		 * be ongoing
		 */
		pin_cvt_fixup(codec, NULL, cvt_nid);
		snd_hda_codec_setup_stream(codec, cvt_nid,
					stream_tag, 0, format);
		goto unlock;
	}

	if (snd_BUG_ON(pin_idx < 0)) {
		err = -EINVAL;
		goto unlock;
	}
	per_pin = get_pin(spec, pin_idx);
	pin_nid = per_pin->pin_nid;

	/* Verify pin:cvt selections to avoid silent audio after S3.
	 * After S3, the audio driver restores pin:cvt selections
	 * but this can happen before gfx is ready and such selection
	 * is overlooked by HW. Thus multiple pins can share a same
	 * default convertor and mute control will affect each other,
	 * which can cause a resumed audio playback become silent
	 * after S3.
	 */
	pin_cvt_fixup(codec, per_pin, 0);

	/* Call sync_audio_rate to set the N/CTS/M manually if necessary */
	/* Todo: add DP1.2 MST audio support later */
	if (codec_has_acomp(codec))
		snd_hdac_sync_audio_rate(&codec->core, pin_nid, per_pin->dev_id,
					 runtime->rate);

	non_pcm = check_non_pcm_per_cvt(codec, cvt_nid);
	mutex_lock(&per_pin->lock);
	per_pin->channels = substream->runtime->channels;
	per_pin->setup = true;

	if (get_wcaps(codec, cvt_nid) & AC_WCAP_STRIPE) {
		stripe = snd_hdac_get_stream_stripe_ctl(&codec->bus->core,
							substream);
		snd_hda_codec_write(codec, cvt_nid, 0,
				    AC_VERB_SET_STRIPE_CONTROL,
				    stripe);
	}

	hdmi_setup_audio_infoframe(codec, per_pin, non_pcm);
	mutex_unlock(&per_pin->lock);
	if (spec->dyn_pin_out) {
		pinctl = snd_hda_codec_read(codec, pin_nid, 0,
					    AC_VERB_GET_PIN_WIDGET_CONTROL, 0);
		snd_hda_codec_write(codec, pin_nid, 0,
				    AC_VERB_SET_PIN_WIDGET_CONTROL,
				    pinctl | PIN_OUT);
	}

	/* snd_hda_set_dev_select() has been called before */
	err = spec->ops.setup_stream(codec, cvt_nid, pin_nid,
				 stream_tag, format);
 unlock:
	mutex_unlock(&spec->pcm_lock);
	return err;
}