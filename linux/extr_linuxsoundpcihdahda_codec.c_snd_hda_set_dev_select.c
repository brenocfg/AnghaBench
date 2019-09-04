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
struct hda_codec {int /*<<< orphan*/  dp_mst; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_SET_DEVICE_SEL ; 
 int EINVAL ; 
 int snd_hda_codec_write (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int snd_hda_get_num_devices (struct hda_codec*,int /*<<< orphan*/ ) ; 

int snd_hda_set_dev_select(struct hda_codec *codec, hda_nid_t nid, int dev_id)
{
	int ret, num_devices;

	/* not support dp_mst will always return 0, using first dev_entry */
	if (!codec->dp_mst)
		return 0;

	/* AC_PAR_DEVLIST_LEN is 0 based. */
	num_devices = snd_hda_get_num_devices(codec, nid) + 1;
	/* If Device List Length is 0 (num_device = 1),
	 * the pin is not multi stream capable.
	 * Do nothing in this case.
	 */
	if (num_devices == 1)
		return 0;

	/* Behavior of setting index being equal to or greater than
	 * Device List Length is not predictable
	 */
	if (num_devices <= dev_id)
		return -EINVAL;

	ret = snd_hda_codec_write(codec, nid, 0,
			AC_VERB_SET_DEVICE_SEL, dev_id);

	return ret;
}