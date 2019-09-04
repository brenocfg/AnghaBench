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
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */

__attribute__((used)) static void hdmi_clear_dip_buffers(struct hda_codec *codec, hda_nid_t pin_nid)
{
#ifdef BE_PARANOID
	int i, j;
	int size;
	int pi, bi;
	for (i = 0; i < 8; i++) {
		size = snd_hda_codec_read(codec, pin_nid, 0,
						AC_VERB_GET_HDMI_DIP_SIZE, i);
		if (size == 0)
			continue;

		hdmi_set_dip_index(codec, pin_nid, i, 0x0);
		for (j = 1; j < 1000; j++) {
			hdmi_write_dip_byte(codec, pin_nid, 0x0);
			hdmi_get_dip_index(codec, pin_nid, &pi, &bi);
			if (pi != i)
				codec_dbg(codec, "dip index %d: %d != %d\n",
						bi, pi, i);
			if (bi == 0) /* byte index wrapped around */
				break;
		}
		codec_dbg(codec,
			"HDMI: DIP GP[%d] buf reported size=%d, written=%d\n",
			i, size, j);
	}
#endif
}