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
 unsigned int AC_ELDD_ELD_DATA ; 
 unsigned int AC_ELDD_ELD_VALID ; 
 int EINVAL ; 
 int ELD_FIXED_BYTES ; 
 int ELD_MAX_SIZE ; 
 int ERANGE ; 
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*) ; 
 int /*<<< orphan*/  codec_info (struct hda_codec*,char*,...) ; 
 unsigned int hdmi_get_eld_data (struct hda_codec*,int /*<<< orphan*/ ,int) ; 
 int snd_hdmi_get_eld_size (struct hda_codec*,int /*<<< orphan*/ ) ; 

int snd_hdmi_get_eld(struct hda_codec *codec, hda_nid_t nid,
		     unsigned char *buf, int *eld_size)
{
	int i;
	int ret = 0;
	int size;

	/*
	 * ELD size is initialized to zero in caller function. If no errors and
	 * ELD is valid, actual eld_size is assigned.
	 */

	size = snd_hdmi_get_eld_size(codec, nid);
	if (size == 0) {
		/* wfg: workaround for ASUS P5E-VM HDMI board */
		codec_info(codec, "HDMI: ELD buf size is 0, force 128\n");
		size = 128;
	}
	if (size < ELD_FIXED_BYTES || size > ELD_MAX_SIZE) {
		codec_info(codec, "HDMI: invalid ELD buf size %d\n", size);
		return -ERANGE;
	}

	/* set ELD buffer */
	for (i = 0; i < size; i++) {
		unsigned int val = hdmi_get_eld_data(codec, nid, i);
		/*
		 * Graphics driver might be writing to ELD buffer right now.
		 * Just abort. The caller will repoll after a while.
		 */
		if (!(val & AC_ELDD_ELD_VALID)) {
			codec_info(codec, "HDMI: invalid ELD data byte %d\n", i);
			ret = -EINVAL;
			goto error;
		}
		val &= AC_ELDD_ELD_DATA;
		/*
		 * The first byte cannot be zero. This can happen on some DVI
		 * connections. Some Intel chips may also need some 250ms delay
		 * to return non-zero ELD data, even when the graphics driver
		 * correctly writes ELD content before setting ELD_valid bit.
		 */
		if (!val && !i) {
			codec_dbg(codec, "HDMI: 0 ELD data\n");
			ret = -EINVAL;
			goto error;
		}
		buf[i] = val;
	}

	*eld_size = size;
error:
	return ret;
}