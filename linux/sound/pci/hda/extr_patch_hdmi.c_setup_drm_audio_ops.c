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
struct TYPE_2__ {int /*<<< orphan*/  master_unbind; int /*<<< orphan*/  master_bind; int /*<<< orphan*/  pin_eld_notify; int /*<<< orphan*/  pin2port; struct hda_codec* audio_ptr; } ;
struct hdmi_spec {TYPE_1__ drm_audio_ops; } ;
struct hda_codec {struct hdmi_spec* spec; } ;
struct drm_audio_component_audio_ops {int /*<<< orphan*/  master_unbind; int /*<<< orphan*/  master_bind; int /*<<< orphan*/  pin_eld_notify; int /*<<< orphan*/  pin2port; } ;

/* Variables and functions */
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void setup_drm_audio_ops(struct hda_codec *codec,
				const struct drm_audio_component_audio_ops *ops)
{
	struct hdmi_spec *spec = codec->spec;

	spec->drm_audio_ops.audio_ptr = codec;
	/* intel_audio_codec_enable() or intel_audio_codec_disable()
	 * will call pin_eld_notify with using audio_ptr pointer
	 * We need make sure audio_ptr is really setup
	 */
	wmb();
	spec->drm_audio_ops.pin2port = ops->pin2port;
	spec->drm_audio_ops.pin_eld_notify = ops->pin_eld_notify;
	spec->drm_audio_ops.master_bind = ops->master_bind;
	spec->drm_audio_ops.master_unbind = ops->master_unbind;
}