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
 int /*<<< orphan*/  AK4671_PLL ; 
 int /*<<< orphan*/  AK4671_PLL_11_2896MHZ ; 
 int /*<<< orphan*/  AK4671_PLL_12MHZ ; 
 int /*<<< orphan*/  AK4671_PLL_12_288MHZ ; 
 int /*<<< orphan*/  AK4671_PLL_13MHZ ; 
 int /*<<< orphan*/  AK4671_PLL_13_5MHZ ; 
 int /*<<< orphan*/  AK4671_PLL_19_2MHZ ; 
 int /*<<< orphan*/  AK4671_PLL_24MHZ ; 
 int /*<<< orphan*/  AK4671_PLL_26MHZ ; 
 int /*<<< orphan*/  AK4671_PLL_27MHZ ; 
 int /*<<< orphan*/  AK4671_PLL_MODE_SELECT0 ; 
 int EINVAL ; 
 int /*<<< orphan*/  snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ak4671_set_dai_sysclk(struct snd_soc_dai *dai, int clk_id,
		unsigned int freq, int dir)
{
	struct snd_soc_component *component = dai->component;
	u8 pll;

	pll = snd_soc_component_read32(component, AK4671_PLL_MODE_SELECT0);
	pll &= ~AK4671_PLL;

	switch (freq) {
	case 11289600:
		pll |= AK4671_PLL_11_2896MHZ;
		break;
	case 12000000:
		pll |= AK4671_PLL_12MHZ;
		break;
	case 12288000:
		pll |= AK4671_PLL_12_288MHZ;
		break;
	case 13000000:
		pll |= AK4671_PLL_13MHZ;
		break;
	case 13500000:
		pll |= AK4671_PLL_13_5MHZ;
		break;
	case 19200000:
		pll |= AK4671_PLL_19_2MHZ;
		break;
	case 24000000:
		pll |= AK4671_PLL_24MHZ;
		break;
	case 26000000:
		pll |= AK4671_PLL_26MHZ;
		break;
	case 27000000:
		pll |= AK4671_PLL_27MHZ;
		break;
	default:
		return -EINVAL;
	}

	snd_soc_component_write(component, AK4671_PLL_MODE_SELECT0, pll);

	return 0;
}