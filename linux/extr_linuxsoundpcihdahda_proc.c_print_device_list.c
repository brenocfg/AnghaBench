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
typedef  int u8 ;
struct snd_info_buffer {int dummy; } ;
struct hda_codec {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int AC_DE_ELDV ; 
 int AC_DE_IA ; 
 int AC_DE_PD ; 
 int AC_MAX_DEV_LIST_LEN ; 
 int /*<<< orphan*/  AC_VERB_GET_DEVICE_SEL ; 
 int snd_hda_codec_read (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_hda_get_devices (struct hda_codec*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 

__attribute__((used)) static void print_device_list(struct snd_info_buffer *buffer,
			    struct hda_codec *codec, hda_nid_t nid)
{
	int i, curr = -1;
	u8 dev_list[AC_MAX_DEV_LIST_LEN];
	int devlist_len;

	devlist_len = snd_hda_get_devices(codec, nid, dev_list,
					AC_MAX_DEV_LIST_LEN);
	snd_iprintf(buffer, "  Devices: %d\n", devlist_len);
	if (devlist_len <= 0)
		return;

	curr = snd_hda_codec_read(codec, nid, 0,
				AC_VERB_GET_DEVICE_SEL, 0);

	for (i = 0; i < devlist_len; i++) {
		if (i == curr)
			snd_iprintf(buffer, "    *");
		else
			snd_iprintf(buffer, "     ");

		snd_iprintf(buffer,
			"Dev %02d: PD = %d, ELDV = %d, IA = %d\n", i,
			!!(dev_list[i] & AC_DE_PD),
			!!(dev_list[i] & AC_DE_ELDV),
			!!(dev_list[i] & AC_DE_IA));
	}
}