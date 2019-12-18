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
struct hdmi_spec_per_pin {int /*<<< orphan*/  mux_idx; int /*<<< orphan*/  dev_id; int /*<<< orphan*/  pin_nid; } ;
struct hda_codec {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  intel_not_share_assigned_cvt (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_not_share_assigned_cvt_nid (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_verify_pin_cvt_connect (struct hda_codec*,struct hdmi_spec_per_pin*) ; 
 int /*<<< orphan*/  snd_hda_set_dev_select (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i915_pin_cvt_fixup(struct hda_codec *codec,
			       struct hdmi_spec_per_pin *per_pin,
			       hda_nid_t cvt_nid)
{
	if (per_pin) {
		snd_hda_set_dev_select(codec, per_pin->pin_nid,
			       per_pin->dev_id);
		intel_verify_pin_cvt_connect(codec, per_pin);
		intel_not_share_assigned_cvt(codec, per_pin->pin_nid,
				     per_pin->dev_id, per_pin->mux_idx);
	} else {
		intel_not_share_assigned_cvt_nid(codec, 0, 0, cvt_nid);
	}
}