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
 int /*<<< orphan*/  AC_VERB_GET_DEVICE_SEL ; 
 int snd_hda_codec_read (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int snd_hda_get_dev_select(struct hda_codec *codec, hda_nid_t nid)
{
	/* not support dp_mst will always return 0, using first dev_entry */
	if (!codec->dp_mst)
		return 0;

	return snd_hda_codec_read(codec, nid, 0, AC_VERB_GET_DEVICE_SEL, 0);
}