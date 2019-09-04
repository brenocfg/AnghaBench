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
 int /*<<< orphan*/  alc_update_coef_idx (struct hda_codec*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_hda_override_conn_list (struct hda_codec*,int,int,int*) ; 

__attribute__((used)) static void alc1220_fixup_clevo_p950(struct hda_codec *codec,
				     const struct hda_fixup *fix,
				     int action)
{
	hda_nid_t conn1[1] = { 0x0c };

	if (action != HDA_FIXUP_ACT_PRE_PROBE)
		return;

	alc_update_coef_idx(codec, 0x7, 0, 0x3c3);
	/* We therefore want to make sure 0x14 (front headphone) and
	 * 0x1b (speakers) use the stereo DAC 0x02
	 */
	snd_hda_override_conn_list(codec, 0x14, 1, conn1);
	snd_hda_override_conn_list(codec, 0x1b, 1, conn1);
}