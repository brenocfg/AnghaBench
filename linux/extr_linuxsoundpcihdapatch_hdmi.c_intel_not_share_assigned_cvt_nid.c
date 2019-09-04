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
struct hdmi_spec {int dummy; } ;
struct hda_codec {struct hdmi_spec* spec; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int intel_cvt_id_to_mux_idx (struct hdmi_spec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_not_share_assigned_cvt (struct hda_codec*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void intel_not_share_assigned_cvt_nid(struct hda_codec *codec,
			hda_nid_t pin_nid, int dev_id, hda_nid_t cvt_nid)
{
	int mux_idx;
	struct hdmi_spec *spec = codec->spec;

	/* On Intel platform, the mapping of converter nid to
	 * mux index of the pins are always the same.
	 * The pin nid may be 0, this means all pins will not
	 * share the converter.
	 */
	mux_idx = intel_cvt_id_to_mux_idx(spec, cvt_nid);
	if (mux_idx >= 0)
		intel_not_share_assigned_cvt(codec, pin_nid, dev_id, mux_idx);
}