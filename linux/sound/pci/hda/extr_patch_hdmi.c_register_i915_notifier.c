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
struct hdmi_spec {int use_acomp_notifier; int /*<<< orphan*/  drm_audio_ops; int /*<<< orphan*/  port2pin; } ;
struct hda_codec {int relaxed_resume; TYPE_1__* bus; struct hdmi_spec* spec; } ;
struct TYPE_2__ {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_audio_ops ; 
 int /*<<< orphan*/  intel_port2pin ; 
 int /*<<< orphan*/  setup_drm_audio_ops (struct hda_codec*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_hdac_acomp_register_notifier (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void register_i915_notifier(struct hda_codec *codec)
{
	struct hdmi_spec *spec = codec->spec;

	spec->use_acomp_notifier = true;
	spec->port2pin = intel_port2pin;
	setup_drm_audio_ops(codec, &intel_audio_ops);
	snd_hdac_acomp_register_notifier(&codec->bus->core,
					&spec->drm_audio_ops);
	/* no need for forcible resume for jack check thanks to notifier */
	codec->relaxed_resume = 1;
}