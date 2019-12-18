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
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int PMADC ; 
 int PMDAC ; 
 int PMVR ; 
 int /*<<< orphan*/  PW_MGMT1 ; 
 int RSTN ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ak4613_set_bias_level(struct snd_soc_component *component,
				 enum snd_soc_bias_level level)
{
	u8 mgmt1 = 0;

	switch (level) {
	case SND_SOC_BIAS_ON:
		mgmt1 |= RSTN;
		/* fall through */
	case SND_SOC_BIAS_PREPARE:
		mgmt1 |= PMADC | PMDAC;
		/* fall through */
	case SND_SOC_BIAS_STANDBY:
		mgmt1 |= PMVR;
		/* fall through */
	case SND_SOC_BIAS_OFF:
	default:
		break;
	}

	snd_soc_component_write(component, PW_MGMT1, mgmt1);

	return 0;
}