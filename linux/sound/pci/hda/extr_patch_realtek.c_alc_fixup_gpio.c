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
 int HDA_FIXUP_ACT_PRE_PROBE ; 
 int /*<<< orphan*/  alc_setup_gpio (struct hda_codec*,unsigned int) ; 

__attribute__((used)) static void alc_fixup_gpio(struct hda_codec *codec, int action,
			   unsigned int mask)
{
	if (action == HDA_FIXUP_ACT_PRE_PROBE)
		alc_setup_gpio(codec, mask);
}