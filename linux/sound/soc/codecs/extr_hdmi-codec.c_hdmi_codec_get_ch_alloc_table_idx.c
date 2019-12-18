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
typedef  int /*<<< orphan*/  u8 ;
struct hdmi_codec_priv {int /*<<< orphan*/  eld; } ;
struct hdmi_codec_cea_spk_alloc {scalar_t__ ca_id; unsigned char n_ch; unsigned long mask; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct hdmi_codec_cea_spk_alloc*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  drm_eld_get_spk_alloc (int /*<<< orphan*/ ) ; 
 struct hdmi_codec_cea_spk_alloc* hdmi_codec_channel_alloc ; 
 unsigned long hdmi_codec_spk_mask_from_alloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hdmi_codec_get_ch_alloc_table_idx(struct hdmi_codec_priv *hcp,
					     unsigned char channels)
{
	int i;
	u8 spk_alloc;
	unsigned long spk_mask;
	const struct hdmi_codec_cea_spk_alloc *cap = hdmi_codec_channel_alloc;

	spk_alloc = drm_eld_get_spk_alloc(hcp->eld);
	spk_mask = hdmi_codec_spk_mask_from_alloc(spk_alloc);

	for (i = 0; i < ARRAY_SIZE(hdmi_codec_channel_alloc); i++, cap++) {
		/* If spk_alloc == 0, HDMI is unplugged return stereo config*/
		if (!spk_alloc && cap->ca_id == 0)
			return i;
		if (cap->n_ch != channels)
			continue;
		if (!(cap->mask == (spk_mask & cap->mask)))
			continue;
		return i;
	}

	return -EINVAL;
}