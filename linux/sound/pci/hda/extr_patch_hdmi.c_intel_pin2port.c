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
struct hdmi_spec {int port_num; int* port_map; } ;
struct hda_codec {struct hdmi_spec* spec; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  codec_info (struct hda_codec*,char*,int) ; 
 int intel_base_nid (struct hda_codec*) ; 

__attribute__((used)) static int intel_pin2port(void *audio_ptr, int pin_nid)
{
	struct hda_codec *codec = audio_ptr;
	struct hdmi_spec *spec = codec->spec;
	int base_nid, i;

	if (!spec->port_num) {
		base_nid = intel_base_nid(codec);
		if (WARN_ON(pin_nid < base_nid || pin_nid >= base_nid + 3))
			return -1;
		return pin_nid - base_nid + 1; /* intel port is 1-based */
	}

	/*
	 * looking for the pin number in the mapping table and return
	 * the index which indicate the port number
	 */
	for (i = 0; i < spec->port_num; i++) {
		if (pin_nid == spec->port_map[i])
			return i + 1;
	}

	/* return -1 if pin number exceeds our expectation */
	codec_info(codec, "Can't find the HDMI/DP port for pin %d\n", pin_nid);
	return -1;
}