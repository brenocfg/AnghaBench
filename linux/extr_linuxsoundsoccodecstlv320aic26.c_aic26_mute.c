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
typedef  int u16 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct aic26 {TYPE_1__* spi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIC26_REG_DAC_GAIN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,struct snd_soc_dai*,int) ; 
 struct aic26* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int aic26_mute(struct snd_soc_dai *dai, int mute)
{
	struct snd_soc_component *component = dai->component;
	struct aic26 *aic26 = snd_soc_component_get_drvdata(component);
	u16 reg;

	dev_dbg(&aic26->spi->dev, "aic26_mute(dai=%p, mute=%i)\n",
		dai, mute);

	if (mute)
		reg = 0x8080;
	else
		reg = 0;
	snd_soc_component_update_bits(component, AIC26_REG_DAC_GAIN, 0x8000, reg);

	return 0;
}