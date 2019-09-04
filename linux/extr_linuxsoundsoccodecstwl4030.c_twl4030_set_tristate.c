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
typedef  int /*<<< orphan*/  u8 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWL4030_AIF_TRI_EN ; 
 int /*<<< orphan*/  TWL4030_REG_AUDIO_IF ; 
 int /*<<< orphan*/  twl4030_read (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int twl4030_write (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl4030_set_tristate(struct snd_soc_dai *dai, int tristate)
{
	struct snd_soc_component *component = dai->component;
	u8 reg = twl4030_read(component, TWL4030_REG_AUDIO_IF);

	if (tristate)
		reg |= TWL4030_AIF_TRI_EN;
	else
		reg &= ~TWL4030_AIF_TRI_EN;

	return twl4030_write(component, TWL4030_REG_AUDIO_IF, reg);
}