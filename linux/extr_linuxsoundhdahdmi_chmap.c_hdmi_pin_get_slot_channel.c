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
struct hdac_device {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_GET_HDMI_CHAN_SLOT ; 
 int snd_hdac_codec_read (struct hdac_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hdmi_pin_get_slot_channel(struct hdac_device *codec,
			hda_nid_t pin_nid, int asp_slot)
{
	return (snd_hdac_codec_read(codec, pin_nid, 0,
				   AC_VERB_GET_HDMI_CHAN_SLOT,
				   asp_slot) & 0xf0) >> 4;
}