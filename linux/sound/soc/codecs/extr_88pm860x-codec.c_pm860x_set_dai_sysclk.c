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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct pm860x_priv {int dir; } ;

/* Variables and functions */
 int EINVAL ; 
 int PM860X_CLK_DIR_OUT ; 
 struct pm860x_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int pm860x_set_dai_sysclk(struct snd_soc_dai *codec_dai,
				 int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_component *component = codec_dai->component;
	struct pm860x_priv *pm860x = snd_soc_component_get_drvdata(component);

	if (dir == PM860X_CLK_DIR_OUT)
		pm860x->dir = PM860X_CLK_DIR_OUT;
	else	/* Slave mode is not supported */
		return -EINVAL;

	return 0;
}