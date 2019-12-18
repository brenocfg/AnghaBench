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
typedef  int u32 ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
typedef  enum da7219_aad_mic_det_thr { ____Placeholder_da7219_aad_mic_det_thr } da7219_aad_mic_det_thr ;

/* Variables and functions */
 int DA7219_AAD_MIC_DET_THR_1000_OHMS ; 
 int DA7219_AAD_MIC_DET_THR_200_OHMS ; 
 int DA7219_AAD_MIC_DET_THR_500_OHMS ; 
 int DA7219_AAD_MIC_DET_THR_750_OHMS ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static enum da7219_aad_mic_det_thr
	da7219_aad_fw_mic_det_thr(struct snd_soc_component *component, u32 val)
{
	switch (val) {
	case 200:
		return DA7219_AAD_MIC_DET_THR_200_OHMS;
	case 500:
		return DA7219_AAD_MIC_DET_THR_500_OHMS;
	case 750:
		return DA7219_AAD_MIC_DET_THR_750_OHMS;
	case 1000:
		return DA7219_AAD_MIC_DET_THR_1000_OHMS;
	default:
		dev_warn(component->dev, "Invalid mic detect threshold");
		return DA7219_AAD_MIC_DET_THR_500_OHMS;
	}
}