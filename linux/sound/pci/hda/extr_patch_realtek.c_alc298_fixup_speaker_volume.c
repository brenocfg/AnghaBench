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

__attribute__((used)) static void alc298_fixup_speaker_volume(struct hda_codec *codec,
					const struct hda_fixup *fix, int action)
{
	if (action == HDA_FIXUP_ACT_PRE_PROBE) {
		/* The speaker is routed to the Node 0x06 by a mistake, as a result
		   we can't adjust the speaker's volume since this node does not has
		   Amp-out capability. we change the speaker's route to:
		   Node 0x02 (Audio Output) -> Node 0x0c (Audio Mixer) -> Node 0x17 (
		   Pin Complex), since Node 0x02 has Amp-out caps, we can adjust
		   speaker's volume now. */

		hda_nid_t conn1[1] = { 0x0c };
		snd_hda_override_conn_list(codec, 0x17, 1, conn1);
	}
}