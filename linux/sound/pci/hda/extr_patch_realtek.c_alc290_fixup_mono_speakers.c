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
 int HDA_FIXUP_ACT_PRE_PROBE ; 
 int /*<<< orphan*/  snd_hda_override_conn_list (struct hda_codec*,int,int,int*) ; 

__attribute__((used)) static void alc290_fixup_mono_speakers(struct hda_codec *codec,
				       const struct hda_fixup *fix, int action)
{
	if (action == HDA_FIXUP_ACT_PRE_PROBE) {
		/* DAC node 0x03 is giving mono output. We therefore want to
		   make sure 0x14 (front speaker) and 0x15 (headphones) use the
		   stereo DAC, while leaving 0x17 (bass speaker) for node 0x03. */
		hda_nid_t conn1[2] = { 0x0c };
		snd_hda_override_conn_list(codec, 0x14, 1, conn1);
		snd_hda_override_conn_list(codec, 0x15, 1, conn1);
	}
}