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
 int /*<<< orphan*/  hdmi_debug_channel_mapping (struct hdac_chmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_manual_setup_channel_mapping (struct hdac_chmap*,int /*<<< orphan*/ ,int,unsigned char*,int) ; 
 int /*<<< orphan*/  hdmi_setup_fake_chmap (unsigned char*,int) ; 
 int /*<<< orphan*/  hdmi_std_setup_channel_mapping (struct hdac_chmap*,int /*<<< orphan*/ ,int,int) ; 

void snd_hdac_setup_channel_mapping(struct hdac_chmap *chmap,
				       hda_nid_t pin_nid, bool non_pcm, int ca,
				       int channels, unsigned char *map,
				       bool chmap_set)
{
	if (!non_pcm && chmap_set) {
		hdmi_manual_setup_channel_mapping(chmap, pin_nid,
						  channels, map, ca);
	} else {
		hdmi_std_setup_channel_mapping(chmap, pin_nid, non_pcm, ca);
		hdmi_setup_fake_chmap(map, ca);
	}

	hdmi_debug_channel_mapping(chmap, pin_nid);
}