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
struct snd_soc_component {int dummy; } ;
struct arizona_priv {struct arizona* arizona; } ;
struct TYPE_2__ {int* gpio_defaults; } ;
struct arizona {int type; TYPE_1__ pdata; } ;

/* Variables and functions */
 int ARIZONA_GPN_FN_MASK ; 
#define  ARIZONA_GP_FN_DRC1_SIGNAL_DETECT 131 
#define  ARIZONA_GP_FN_DRC2_SIGNAL_DETECT 130 
 int ARRAY_SIZE (int*) ; 
#define  WM5110 129 
#define  WM8280 128 
 int /*<<< orphan*/  snd_soc_component_disable_pin (struct snd_soc_component*,char*) ; 
 int /*<<< orphan*/  snd_soc_component_enable_pin (struct snd_soc_component*,char*) ; 
 struct arizona_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

int arizona_init_gpio(struct snd_soc_component *component)
{
	struct arizona_priv *priv = snd_soc_component_get_drvdata(component);
	struct arizona *arizona = priv->arizona;
	int i;

	switch (arizona->type) {
	case WM5110:
	case WM8280:
		snd_soc_component_disable_pin(component,
					      "DRC2 Signal Activity");
		break;
	default:
		break;
	}

	snd_soc_component_disable_pin(component, "DRC1 Signal Activity");

	for (i = 0; i < ARRAY_SIZE(arizona->pdata.gpio_defaults); i++) {
		switch (arizona->pdata.gpio_defaults[i] & ARIZONA_GPN_FN_MASK) {
		case ARIZONA_GP_FN_DRC1_SIGNAL_DETECT:
			snd_soc_component_enable_pin(component,
						     "DRC1 Signal Activity");
			break;
		case ARIZONA_GP_FN_DRC2_SIGNAL_DETECT:
			snd_soc_component_enable_pin(component,
						     "DRC2 Signal Activity");
			break;
		default:
			break;
		}
	}

	return 0;
}