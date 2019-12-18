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
struct hdmi_spec {int (* port2pin ) (struct hda_codec*,int) ;int acomp_registered; int /*<<< orphan*/  drm_audio_ops; } ;
struct hda_codec {TYPE_1__* bus; struct hdmi_spec* spec; } ;
struct drm_audio_component_audio_ops {int dummy; } ;
struct TYPE_2__ {scalar_t__ keep_power; int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  match_bound_vga ; 
 int /*<<< orphan*/  setup_drm_audio_ops (struct hda_codec*,struct drm_audio_component_audio_ops const*) ; 
 int /*<<< orphan*/  snd_hdac_acomp_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void generic_acomp_init(struct hda_codec *codec,
			       const struct drm_audio_component_audio_ops *ops,
			       int (*port2pin)(struct hda_codec *, int))
{
	struct hdmi_spec *spec = codec->spec;

	spec->port2pin = port2pin;
	setup_drm_audio_ops(codec, ops);
	if (!snd_hdac_acomp_init(&codec->bus->core, &spec->drm_audio_ops,
				 match_bound_vga, 0)) {
		spec->acomp_registered = true;
		codec->bus->keep_power = 0;
	}
}