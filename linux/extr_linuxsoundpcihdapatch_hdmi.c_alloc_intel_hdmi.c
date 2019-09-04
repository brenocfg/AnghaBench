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
struct hda_codec {int /*<<< orphan*/  probe_id; TYPE_2__* bus; } ;
struct TYPE_3__ {int /*<<< orphan*/  audio_component; } ;
struct TYPE_4__ {TYPE_1__ core; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  HDA_CODEC_ID_SKIP_PROBE ; 
 int alloc_generic_hdmi (struct hda_codec*) ; 
 int /*<<< orphan*/  codec_info (struct hda_codec*,char*) ; 

__attribute__((used)) static int alloc_intel_hdmi(struct hda_codec *codec)
{
	/* requires i915 binding */
	if (!codec->bus->core.audio_component) {
		codec_info(codec, "No i915 binding for Intel HDMI/DP codec\n");
		/* set probe_id here to prevent generic fallback binding */
		codec->probe_id = HDA_CODEC_ID_SKIP_PROBE;
		return -ENODEV;
	}

	return alloc_generic_hdmi(codec);
}