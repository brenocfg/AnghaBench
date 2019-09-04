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
struct cx20442_priv {int /*<<< orphan*/  por; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int const snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct cx20442_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int cx20442_set_bias_level(struct snd_soc_component *component,
		enum snd_soc_bias_level level)
{
	struct cx20442_priv *cx20442 = snd_soc_component_get_drvdata(component);
	int err = 0;

	switch (level) {
	case SND_SOC_BIAS_PREPARE:
		if (snd_soc_component_get_bias_level(component) != SND_SOC_BIAS_STANDBY)
			break;
		if (IS_ERR(cx20442->por))
			err = PTR_ERR(cx20442->por);
		else
			err = regulator_enable(cx20442->por);
		break;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_level(component) != SND_SOC_BIAS_PREPARE)
			break;
		if (IS_ERR(cx20442->por))
			err = PTR_ERR(cx20442->por);
		else
			err = regulator_disable(cx20442->por);
		break;
	default:
		break;
	}

	return err;
}