#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct hdmi_codec_priv {TYPE_1__* chmap_info; int /*<<< orphan*/  eld; } ;
struct TYPE_2__ {int max_channels; int /*<<< orphan*/  chmap; } ;

/* Variables and functions */
 unsigned long FL ; 
 unsigned long FR ; 
 int /*<<< orphan*/  drm_eld_get_spk_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_codec_8ch_chmaps ; 
 unsigned long hdmi_codec_spk_mask_from_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_codec_stereo_chmaps ; 

__attribute__((used)) static void hdmi_codec_eld_chmap(struct hdmi_codec_priv *hcp)
{
	u8 spk_alloc;
	unsigned long spk_mask;

	spk_alloc = drm_eld_get_spk_alloc(hcp->eld);
	spk_mask = hdmi_codec_spk_mask_from_alloc(spk_alloc);

	/* Detect if only stereo supported, else return 8 channels mappings */
	if ((spk_mask & ~(FL | FR)) && hcp->chmap_info->max_channels > 2)
		hcp->chmap_info->chmap = hdmi_codec_8ch_chmaps;
	else
		hcp->chmap_info->chmap = hdmi_codec_stereo_chmaps;
}