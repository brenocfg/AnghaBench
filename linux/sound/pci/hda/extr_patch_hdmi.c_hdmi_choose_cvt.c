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
struct hdmi_spec_per_pin {int num_mux_nids; scalar_t__* mux_nids; int mux_idx; } ;
struct hdmi_spec_per_cvt {scalar_t__ cvt_nid; scalar_t__ assigned; } ;
struct hdmi_spec {int num_cvts; } ;
struct hda_codec {struct hdmi_spec* spec; } ;

/* Variables and functions */
 int EBUSY ; 
 struct hdmi_spec_per_cvt* get_cvt (struct hdmi_spec*,int) ; 
 struct hdmi_spec_per_pin* get_pin (struct hdmi_spec*,int) ; 

__attribute__((used)) static int hdmi_choose_cvt(struct hda_codec *codec,
			   int pin_idx, int *cvt_id)
{
	struct hdmi_spec *spec = codec->spec;
	struct hdmi_spec_per_pin *per_pin;
	struct hdmi_spec_per_cvt *per_cvt = NULL;
	int cvt_idx, mux_idx = 0;

	/* pin_idx < 0 means no pin will be bound to the converter */
	if (pin_idx < 0)
		per_pin = NULL;
	else
		per_pin = get_pin(spec, pin_idx);

	/* Dynamically assign converter to stream */
	for (cvt_idx = 0; cvt_idx < spec->num_cvts; cvt_idx++) {
		per_cvt = get_cvt(spec, cvt_idx);

		/* Must not already be assigned */
		if (per_cvt->assigned)
			continue;
		if (per_pin == NULL)
			break;
		/* Must be in pin's mux's list of converters */
		for (mux_idx = 0; mux_idx < per_pin->num_mux_nids; mux_idx++)
			if (per_pin->mux_nids[mux_idx] == per_cvt->cvt_nid)
				break;
		/* Not in mux list */
		if (mux_idx == per_pin->num_mux_nids)
			continue;
		break;
	}

	/* No free converters */
	if (cvt_idx == spec->num_cvts)
		return -EBUSY;

	if (per_pin != NULL)
		per_pin->mux_idx = mux_idx;

	if (cvt_id)
		*cvt_id = cvt_idx;

	return 0;
}