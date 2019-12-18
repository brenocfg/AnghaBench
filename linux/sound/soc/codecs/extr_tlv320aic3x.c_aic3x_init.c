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
struct snd_soc_component {int dummy; } ;
struct aic3x_priv {int model; int ocmv; } ;

/* Variables and functions */
#define  AIC3X_MODEL_3007 130 
 int AIC3X_MODEL_3104 ; 
#define  AIC3X_MODEL_33 129 
#define  AIC3X_MODEL_3X 128 
 int /*<<< orphan*/  AIC3X_PAGE_SELECT ; 
 int /*<<< orphan*/  AIC3X_RESET ; 
 int /*<<< orphan*/  CLASSD_CTRL ; 
 int /*<<< orphan*/  DACL1_2_HPLCOM_VOL ; 
 int /*<<< orphan*/  DACL1_2_HPLOUT_VOL ; 
 int /*<<< orphan*/  DACL1_2_LLOPM_VOL ; 
 int /*<<< orphan*/  DACR1_2_HPRCOM_VOL ; 
 int /*<<< orphan*/  DACR1_2_HPROUT_VOL ; 
 int /*<<< orphan*/  DACR1_2_RLOPM_VOL ; 
 int DEFAULT_GAIN ; 
 int DEFAULT_VOL ; 
 int /*<<< orphan*/  HPLCOM_CTRL ; 
 int /*<<< orphan*/  HPLOUT_CTRL ; 
 int /*<<< orphan*/  HPOUT_SC ; 
 int HPOUT_SC_OCMV_MASK ; 
 int HPOUT_SC_OCMV_SHIFT ; 
 int /*<<< orphan*/  HPRCOM_CTRL ; 
 int /*<<< orphan*/  HPROUT_CTRL ; 
 int /*<<< orphan*/  LADC_VOL ; 
 int /*<<< orphan*/  LDAC_VOL ; 
 int /*<<< orphan*/  LINE1L_2_LADC_CTRL ; 
 int /*<<< orphan*/  LINE1R_2_RADC_CTRL ; 
 int /*<<< orphan*/  LINE2L_2_HPLCOM_VOL ; 
 int /*<<< orphan*/  LINE2L_2_HPLOUT_VOL ; 
 int /*<<< orphan*/  LINE2L_2_LLOPM_VOL ; 
 int /*<<< orphan*/  LINE2R_2_HPRCOM_VOL ; 
 int /*<<< orphan*/  LINE2R_2_HPROUT_VOL ; 
 int /*<<< orphan*/  LINE2R_2_RLOPM_VOL ; 
 int /*<<< orphan*/  LLOPM_CTRL ; 
 int MUTE_ON ; 
 int PAGE0_SELECT ; 
 int /*<<< orphan*/  PGAL_2_HPLCOM_VOL ; 
 int /*<<< orphan*/  PGAL_2_HPLOUT_VOL ; 
 int /*<<< orphan*/  PGAL_2_LLOPM_VOL ; 
 int /*<<< orphan*/  PGAR_2_HPRCOM_VOL ; 
 int /*<<< orphan*/  PGAR_2_HPROUT_VOL ; 
 int /*<<< orphan*/  PGAR_2_RLOPM_VOL ; 
 int /*<<< orphan*/  RADC_VOL ; 
 int /*<<< orphan*/  RDAC_VOL ; 
 int /*<<< orphan*/  RLOPM_CTRL ; 
 int ROUTE_ON ; 
 int SOFT_RESET ; 
 int UNMUTE ; 
 int /*<<< orphan*/  aic3x_mono_init (struct snd_soc_component*) ; 
 struct aic3x_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int aic3x_init(struct snd_soc_component *component)
{
	struct aic3x_priv *aic3x = snd_soc_component_get_drvdata(component);

	snd_soc_component_write(component, AIC3X_PAGE_SELECT, PAGE0_SELECT);
	snd_soc_component_write(component, AIC3X_RESET, SOFT_RESET);

	/* DAC default volume and mute */
	snd_soc_component_write(component, LDAC_VOL, DEFAULT_VOL | MUTE_ON);
	snd_soc_component_write(component, RDAC_VOL, DEFAULT_VOL | MUTE_ON);

	/* DAC to HP default volume and route to Output mixer */
	snd_soc_component_write(component, DACL1_2_HPLOUT_VOL, DEFAULT_VOL | ROUTE_ON);
	snd_soc_component_write(component, DACR1_2_HPROUT_VOL, DEFAULT_VOL | ROUTE_ON);
	snd_soc_component_write(component, DACL1_2_HPLCOM_VOL, DEFAULT_VOL | ROUTE_ON);
	snd_soc_component_write(component, DACR1_2_HPRCOM_VOL, DEFAULT_VOL | ROUTE_ON);
	/* DAC to Line Out default volume and route to Output mixer */
	snd_soc_component_write(component, DACL1_2_LLOPM_VOL, DEFAULT_VOL | ROUTE_ON);
	snd_soc_component_write(component, DACR1_2_RLOPM_VOL, DEFAULT_VOL | ROUTE_ON);

	/* unmute all outputs */
	snd_soc_component_update_bits(component, LLOPM_CTRL, UNMUTE, UNMUTE);
	snd_soc_component_update_bits(component, RLOPM_CTRL, UNMUTE, UNMUTE);
	snd_soc_component_update_bits(component, HPLOUT_CTRL, UNMUTE, UNMUTE);
	snd_soc_component_update_bits(component, HPROUT_CTRL, UNMUTE, UNMUTE);
	snd_soc_component_update_bits(component, HPLCOM_CTRL, UNMUTE, UNMUTE);
	snd_soc_component_update_bits(component, HPRCOM_CTRL, UNMUTE, UNMUTE);

	/* ADC default volume and unmute */
	snd_soc_component_write(component, LADC_VOL, DEFAULT_GAIN);
	snd_soc_component_write(component, RADC_VOL, DEFAULT_GAIN);
	/* By default route Line1 to ADC PGA mixer */
	snd_soc_component_write(component, LINE1L_2_LADC_CTRL, 0x0);
	snd_soc_component_write(component, LINE1R_2_RADC_CTRL, 0x0);

	/* PGA to HP Bypass default volume, disconnect from Output Mixer */
	snd_soc_component_write(component, PGAL_2_HPLOUT_VOL, DEFAULT_VOL);
	snd_soc_component_write(component, PGAR_2_HPROUT_VOL, DEFAULT_VOL);
	snd_soc_component_write(component, PGAL_2_HPLCOM_VOL, DEFAULT_VOL);
	snd_soc_component_write(component, PGAR_2_HPRCOM_VOL, DEFAULT_VOL);
	/* PGA to Line Out default volume, disconnect from Output Mixer */
	snd_soc_component_write(component, PGAL_2_LLOPM_VOL, DEFAULT_VOL);
	snd_soc_component_write(component, PGAR_2_RLOPM_VOL, DEFAULT_VOL);

	/* On tlv320aic3104, these registers are reserved and must not be written */
	if (aic3x->model != AIC3X_MODEL_3104) {
		/* Line2 to HP Bypass default volume, disconnect from Output Mixer */
		snd_soc_component_write(component, LINE2L_2_HPLOUT_VOL, DEFAULT_VOL);
		snd_soc_component_write(component, LINE2R_2_HPROUT_VOL, DEFAULT_VOL);
		snd_soc_component_write(component, LINE2L_2_HPLCOM_VOL, DEFAULT_VOL);
		snd_soc_component_write(component, LINE2R_2_HPRCOM_VOL, DEFAULT_VOL);
		/* Line2 Line Out default volume, disconnect from Output Mixer */
		snd_soc_component_write(component, LINE2L_2_LLOPM_VOL, DEFAULT_VOL);
		snd_soc_component_write(component, LINE2R_2_RLOPM_VOL, DEFAULT_VOL);
	}

	switch (aic3x->model) {
	case AIC3X_MODEL_3X:
	case AIC3X_MODEL_33:
		aic3x_mono_init(component);
		break;
	case AIC3X_MODEL_3007:
		snd_soc_component_write(component, CLASSD_CTRL, 0);
		break;
	}

	/*  Output common-mode voltage = 1.5 V */
	snd_soc_component_update_bits(component, HPOUT_SC, HPOUT_SC_OCMV_MASK,
			    aic3x->ocmv << HPOUT_SC_OCMV_SHIFT);

	return 0;
}