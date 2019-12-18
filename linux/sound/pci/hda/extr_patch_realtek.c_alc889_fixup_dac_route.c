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
 int HDA_FIXUP_ACT_PROBE ; 
 int /*<<< orphan*/  snd_hda_override_conn_list (struct hda_codec*,int,int,int*) ; 

__attribute__((used)) static void alc889_fixup_dac_route(struct hda_codec *codec,
				   const struct hda_fixup *fix, int action)
{
	if (action == HDA_FIXUP_ACT_PRE_PROBE) {
		/* fake the connections during parsing the tree */
		hda_nid_t conn1[2] = { 0x0c, 0x0d };
		hda_nid_t conn2[2] = { 0x0e, 0x0f };
		snd_hda_override_conn_list(codec, 0x14, 2, conn1);
		snd_hda_override_conn_list(codec, 0x15, 2, conn1);
		snd_hda_override_conn_list(codec, 0x18, 2, conn2);
		snd_hda_override_conn_list(codec, 0x1a, 2, conn2);
	} else if (action == HDA_FIXUP_ACT_PROBE) {
		/* restore the connections */
		hda_nid_t conn[5] = { 0x0c, 0x0d, 0x0e, 0x0f, 0x26 };
		snd_hda_override_conn_list(codec, 0x14, 5, conn);
		snd_hda_override_conn_list(codec, 0x15, 5, conn);
		snd_hda_override_conn_list(codec, 0x18, 5, conn);
		snd_hda_override_conn_list(codec, 0x1a, 5, conn);
	}
}