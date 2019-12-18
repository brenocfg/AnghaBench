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
struct hda_fixup {int dummy; } ;
struct hda_codec {int dummy; } ;
typedef  int hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 int HDA_FIXUP_ACT_INIT ; 
 int /*<<< orphan*/  alc889_fixup_mac_pins (struct hda_codec*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void alc889_fixup_mba21_vref(struct hda_codec *codec,
				    const struct hda_fixup *fix, int action)
{
	static hda_nid_t nids[2] = { 0x18, 0x19 };

	if (action == HDA_FIXUP_ACT_INIT)
		alc889_fixup_mac_pins(codec, nids, ARRAY_SIZE(nids));
}