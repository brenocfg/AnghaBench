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
struct hdmi_spec_per_pin {int num_mux_nids; scalar_t__* mux_nids; } ;
struct hdmi_spec {int dummy; } ;
typedef  scalar_t__ hda_nid_t ;

/* Variables and functions */

__attribute__((used)) static int hdmi_get_pin_cvt_mux(struct hdmi_spec *spec,
		struct hdmi_spec_per_pin *per_pin, hda_nid_t cvt_nid)
{
	int mux_idx;

	for (mux_idx = 0; mux_idx < per_pin->num_mux_nids; mux_idx++)
		if (per_pin->mux_nids[mux_idx] == cvt_nid)
			break;
	return mux_idx;
}