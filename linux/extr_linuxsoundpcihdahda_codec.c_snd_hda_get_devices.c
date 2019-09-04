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
typedef  scalar_t__ u8 ;
struct hda_codec {int /*<<< orphan*/  core; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_GET_DEVICE_LIST ; 
 unsigned int snd_hda_get_num_devices (struct hda_codec*,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_hdac_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int*) ; 

int snd_hda_get_devices(struct hda_codec *codec, hda_nid_t nid,
			u8 *dev_list, int max_devices)
{
	unsigned int parm;
	int i, dev_len, devices;

	parm = snd_hda_get_num_devices(codec, nid);
	if (!parm)	/* not multi-stream capable */
		return 0;

	dev_len = parm + 1;
	dev_len = dev_len < max_devices ? dev_len : max_devices;

	devices = 0;
	while (devices < dev_len) {
		if (snd_hdac_read(&codec->core, nid,
				  AC_VERB_GET_DEVICE_LIST, devices, &parm))
			break; /* error */

		for (i = 0; i < 8; i++) {
			dev_list[devices] = (u8)parm;
			parm >>= 4;
			devices++;
			if (devices >= dev_len)
				break;
		}
	}
	return devices;
}