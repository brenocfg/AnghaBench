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
struct hdmi_spec_per_pin {scalar_t__ pin_nid; int dev_id; } ;
struct hdmi_spec {int num_pins; } ;
struct hda_codec {struct hdmi_spec* spec; } ;
typedef  scalar_t__ hda_nid_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  codec_warn (struct hda_codec*,char*,scalar_t__) ; 
 struct hdmi_spec_per_pin* get_pin (struct hdmi_spec*,int) ; 

__attribute__((used)) static int pin_id_to_pin_index(struct hda_codec *codec,
			       hda_nid_t pin_nid, int dev_id)
{
	struct hdmi_spec *spec = codec->spec;
	int pin_idx;
	struct hdmi_spec_per_pin *per_pin;

	/*
	 * (dev_id == -1) means it is NON-MST pin
	 * return the first virtual pin on this port
	 */
	if (dev_id == -1)
		dev_id = 0;

	for (pin_idx = 0; pin_idx < spec->num_pins; pin_idx++) {
		per_pin = get_pin(spec, pin_idx);
		if ((per_pin->pin_nid == pin_nid) &&
			(per_pin->dev_id == dev_id))
			return pin_idx;
	}

	codec_warn(codec, "HDMI: pin nid %d not registered\n", pin_nid);
	return -EINVAL;
}