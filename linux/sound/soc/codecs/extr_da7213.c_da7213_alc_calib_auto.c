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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DA7213_ALC_AUTO_CALIB_EN ; 
 int DA7213_ALC_CALIB_OVERFLOW ; 
 int /*<<< orphan*/  DA7213_ALC_CTRL1 ; 
 int DA7213_ALC_OFFSET_EN ; 
 int DA7213_ALC_SYNC_MODE ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void da7213_alc_calib_auto(struct snd_soc_component *component)
{
	u8 alc_ctrl1;

	/* Begin auto calibration and wait for completion */
	snd_soc_component_update_bits(component, DA7213_ALC_CTRL1, DA7213_ALC_AUTO_CALIB_EN,
			    DA7213_ALC_AUTO_CALIB_EN);
	do {
		alc_ctrl1 = snd_soc_component_read32(component, DA7213_ALC_CTRL1);
	} while (alc_ctrl1 & DA7213_ALC_AUTO_CALIB_EN);

	/* If auto calibration fails, fall back to digital gain only mode */
	if (alc_ctrl1 & DA7213_ALC_CALIB_OVERFLOW) {
		dev_warn(component->dev,
			 "ALC auto calibration failed with overflow\n");
		snd_soc_component_update_bits(component, DA7213_ALC_CTRL1,
				    DA7213_ALC_OFFSET_EN | DA7213_ALC_SYNC_MODE,
				    0);
	} else {
		/* Enable analog/digital gain mode & offset cancellation */
		snd_soc_component_update_bits(component, DA7213_ALC_CTRL1,
				    DA7213_ALC_OFFSET_EN | DA7213_ALC_SYNC_MODE,
				    DA7213_ALC_OFFSET_EN | DA7213_ALC_SYNC_MODE);
	}

}