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
struct hda_codec {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATI_VERB_SET_CHANNEL_ALLOCATION ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void atihdmi_pin_setup_infoframe(struct hda_codec *codec, hda_nid_t pin_nid, int ca,
					int active_channels, int conn_type)
{
	snd_hda_codec_write(codec, pin_nid, 0, ATI_VERB_SET_CHANNEL_ALLOCATION, ca);
}