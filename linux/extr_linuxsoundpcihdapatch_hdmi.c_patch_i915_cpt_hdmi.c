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
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int alloc_intel_hdmi (struct hda_codec*) ; 
 int parse_intel_hdmi (struct hda_codec*) ; 

__attribute__((used)) static int patch_i915_cpt_hdmi(struct hda_codec *codec)
{
	int err;

	err = alloc_intel_hdmi(codec);
	if (err < 0)
		return err;
	return parse_intel_hdmi(codec);
}