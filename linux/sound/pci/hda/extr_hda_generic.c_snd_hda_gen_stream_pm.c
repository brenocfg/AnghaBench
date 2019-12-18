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
struct hda_codec {scalar_t__ power_save_node; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  set_path_power (struct hda_codec*,int /*<<< orphan*/ ,int,int) ; 

void snd_hda_gen_stream_pm(struct hda_codec *codec, hda_nid_t nid, bool on)
{
	if (codec->power_save_node)
		set_path_power(codec, nid, -1, on);
}