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
struct hdac_chmap {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */

__attribute__((used)) static void hdmi_debug_channel_mapping(struct hdac_chmap *chmap,
				       hda_nid_t pin_nid)
{
#ifdef CONFIG_SND_DEBUG_VERBOSE
	int i;
	int channel;

	for (i = 0; i < 8; i++) {
		channel = chmap->ops.pin_get_slot_channel(
				chmap->hdac, pin_nid, i);
		dev_dbg(&chmap->hdac->dev, "HDMI: ASP channel %d => slot %d\n",
						channel, i);
	}
#endif
}