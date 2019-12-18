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
struct snd_soc_component {int dummy; } ;
struct da7219_priv {scalar_t__ mic_pga_delay; int /*<<< orphan*/  wakeup_source; struct da7219_pdata* pdata; } ;
struct da7219_pdata {int micbias_lvl; int mic_amp_in_sel; int /*<<< orphan*/  wakeup_source; } ;

/* Variables and functions */
 int DA7219_MICBIAS1_LEVEL_SHIFT ; 
#define  DA7219_MICBIAS_1_6V 136 
#define  DA7219_MICBIAS_1_8V 135 
#define  DA7219_MICBIAS_2_0V 134 
#define  DA7219_MICBIAS_2_2V 133 
#define  DA7219_MICBIAS_2_4V 132 
#define  DA7219_MICBIAS_2_6V 131 
 int /*<<< orphan*/  DA7219_MICBIAS_CTRL ; 
 int /*<<< orphan*/  DA7219_MIC_1_SELECT ; 
#define  DA7219_MIC_AMP_IN_SEL_DIFF 130 
#define  DA7219_MIC_AMP_IN_SEL_SE_N 129 
#define  DA7219_MIC_AMP_IN_SEL_SE_P 128 
 scalar_t__ DA7219_MIC_PGA_BASE_DELAY ; 
 int DA7219_MIC_PGA_OFFSET_DELAY ; 
 struct da7219_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void da7219_handle_pdata(struct snd_soc_component *component)
{
	struct da7219_priv *da7219 = snd_soc_component_get_drvdata(component);
	struct da7219_pdata *pdata = da7219->pdata;

	if (pdata) {
		u8 micbias_lvl = 0;

		da7219->wakeup_source = pdata->wakeup_source;

		/* Mic Bias voltages */
		switch (pdata->micbias_lvl) {
		case DA7219_MICBIAS_1_6V:
		case DA7219_MICBIAS_1_8V:
		case DA7219_MICBIAS_2_0V:
		case DA7219_MICBIAS_2_2V:
		case DA7219_MICBIAS_2_4V:
		case DA7219_MICBIAS_2_6V:
			micbias_lvl |= (pdata->micbias_lvl <<
					DA7219_MICBIAS1_LEVEL_SHIFT);
			break;
		}

		snd_soc_component_write(component, DA7219_MICBIAS_CTRL, micbias_lvl);

		/*
		 * Calculate delay required to compensate for DC offset in
		 * Mic PGA, based on Mic Bias voltage.
		 */
		da7219->mic_pga_delay =  DA7219_MIC_PGA_BASE_DELAY +
					(pdata->micbias_lvl *
					 DA7219_MIC_PGA_OFFSET_DELAY);

		/* Mic */
		switch (pdata->mic_amp_in_sel) {
		case DA7219_MIC_AMP_IN_SEL_DIFF:
		case DA7219_MIC_AMP_IN_SEL_SE_P:
		case DA7219_MIC_AMP_IN_SEL_SE_N:
			snd_soc_component_write(component, DA7219_MIC_1_SELECT,
				      pdata->mic_amp_in_sel);
			break;
		}
	}
}