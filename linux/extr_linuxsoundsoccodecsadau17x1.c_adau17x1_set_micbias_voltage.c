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
struct adau {int /*<<< orphan*/  regmap; } ;
typedef  enum adau17x1_micbias_voltage { ____Placeholder_adau17x1_micbias_voltage } adau17x1_micbias_voltage ;

/* Variables and functions */
 int /*<<< orphan*/  ADAU17X1_MICBIAS ; 
#define  ADAU17X1_MICBIAS_0_65_AVDD 129 
#define  ADAU17X1_MICBIAS_0_90_AVDD 128 
 int EINVAL ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct adau* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

int adau17x1_set_micbias_voltage(struct snd_soc_component *component,
	enum adau17x1_micbias_voltage micbias)
{
	struct adau *adau = snd_soc_component_get_drvdata(component);

	switch (micbias) {
	case ADAU17X1_MICBIAS_0_90_AVDD:
	case ADAU17X1_MICBIAS_0_65_AVDD:
		break;
	default:
		return -EINVAL;
	}

	return regmap_write(adau->regmap, ADAU17X1_MICBIAS, micbias << 2);
}