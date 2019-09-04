#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  pin_cvt_fixup; int /*<<< orphan*/  setup_stream; } ;
struct hdmi_spec {int dyn_pcm_assign; TYPE_3__ ops; int /*<<< orphan*/  vendor_nid; } ;
struct TYPE_5__ {int /*<<< orphan*/  set_power_state; } ;
struct TYPE_4__ {int link_power_control; } ;
struct hda_codec {int dp_mst; int auto_runtime_pm; scalar_t__ depop_delay; TYPE_2__ patch_ops; TYPE_1__ core; struct hdmi_spec* spec; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int alloc_intel_hdmi (struct hda_codec*) ; 
 int /*<<< orphan*/  haswell_set_power_state ; 
 int /*<<< orphan*/  i915_hsw_setup_stream ; 
 int /*<<< orphan*/  i915_pin_cvt_fixup ; 
 int /*<<< orphan*/  intel_haswell_enable_all_pins (struct hda_codec*,int) ; 
 int /*<<< orphan*/  intel_haswell_fixup_enable_dp12 (struct hda_codec*) ; 
 int /*<<< orphan*/  is_broadwell (struct hda_codec*) ; 
 int /*<<< orphan*/  is_haswell (struct hda_codec*) ; 
 int parse_intel_hdmi (struct hda_codec*) ; 

__attribute__((used)) static int intel_hsw_common_init(struct hda_codec *codec, hda_nid_t vendor_nid)
{
	struct hdmi_spec *spec;
	int err;

	err = alloc_intel_hdmi(codec);
	if (err < 0)
		return err;
	spec = codec->spec;
	codec->dp_mst = true;
	spec->dyn_pcm_assign = true;
	spec->vendor_nid = vendor_nid;

	intel_haswell_enable_all_pins(codec, true);
	intel_haswell_fixup_enable_dp12(codec);

	/* For Haswell/Broadwell, the controller is also in the power well and
	 * can cover the codec power request, and so need not set this flag.
	 */
	if (!is_haswell(codec) && !is_broadwell(codec))
		codec->core.link_power_control = 1;

	codec->patch_ops.set_power_state = haswell_set_power_state;
	codec->depop_delay = 0;
	codec->auto_runtime_pm = 1;

	spec->ops.setup_stream = i915_hsw_setup_stream;
	spec->ops.pin_cvt_fixup = i915_pin_cvt_fixup;

	return parse_intel_hdmi(codec);
}