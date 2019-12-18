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
struct hda_codec {int /*<<< orphan*/  fixup_id; scalar_t__ fixup_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  apply_fixup (struct hda_codec*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void snd_hda_apply_fixup(struct hda_codec *codec, int action)
{
	if (codec->fixup_list)
		apply_fixup(codec, codec->fixup_id, action, 0);
}