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

/* Variables and functions */
 int /*<<< orphan*/  __analog_low_current_mode (struct hda_codec*,int) ; 
 int /*<<< orphan*/  snd_hda_gen_init (struct hda_codec*) ; 
 int /*<<< orphan*/  vt1708_update_hp_work (struct hda_codec*) ; 

__attribute__((used)) static int via_init(struct hda_codec *codec)
{
	/* init power states */
	__analog_low_current_mode(codec, true);

	snd_hda_gen_init(codec);

	vt1708_update_hp_work(codec);

	return 0;
}