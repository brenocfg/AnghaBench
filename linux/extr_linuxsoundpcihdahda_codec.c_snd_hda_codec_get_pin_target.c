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
struct hda_pincfg {int target; } ;
struct hda_codec {int /*<<< orphan*/  init_pins; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 struct hda_pincfg* look_up_pincfg (struct hda_codec*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int snd_hda_codec_get_pin_target(struct hda_codec *codec, hda_nid_t nid)
{
	struct hda_pincfg *pin;

	pin = look_up_pincfg(codec, &codec->init_pins, nid);
	if (!pin)
		return 0;
	return pin->target;
}