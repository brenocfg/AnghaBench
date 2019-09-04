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
struct TYPE_4__ {int /*<<< orphan*/  pin_eld_notify; int /*<<< orphan*/  pin2port; struct hda_codec* audio_ptr; } ;
struct hdmi_spec {int use_acomp_notifier; TYPE_2__ drm_audio_ops; } ;
struct hda_codec {TYPE_1__* bus; struct hdmi_spec* spec; } ;
struct TYPE_3__ {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_pin2port ; 
 int /*<<< orphan*/  intel_pin_eld_notify ; 
 int /*<<< orphan*/  snd_hdac_acomp_register_notifier (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void register_i915_notifier(struct hda_codec *codec)
{
	struct hdmi_spec *spec = codec->spec;

	spec->use_acomp_notifier = true;
	spec->drm_audio_ops.audio_ptr = codec;
	/* intel_audio_codec_enable() or intel_audio_codec_disable()
	 * will call pin_eld_notify with using audio_ptr pointer
	 * We need make sure audio_ptr is really setup
	 */
	wmb();
	spec->drm_audio_ops.pin2port = intel_pin2port;
	spec->drm_audio_ops.pin_eld_notify = intel_pin_eld_notify;
	snd_hdac_acomp_register_notifier(&codec->bus->core,
					&spec->drm_audio_ops);
}