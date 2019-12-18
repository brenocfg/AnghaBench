#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uniphier_aio {int plldiv; int pll_out; int pll_in; TYPE_2__* chip; } ;
struct snd_soc_dai {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int num_plls; TYPE_1__* pdev; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
#define  AUD_CLK_A 138 
#define  AUD_CLK_A1 137 
#define  AUD_CLK_A2 136 
#define  AUD_CLK_APLL 135 
#define  AUD_CLK_F 134 
#define  AUD_CLK_F1 133 
#define  AUD_CLK_F2 132 
#define  AUD_CLK_HSC0 131 
#define  AUD_CLK_IO 130 
#define  AUD_CLK_RX0 129 
#define  AUD_CLK_USB0 128 
 int AUD_PLL_A1 ; 
 int AUD_PLL_A2 ; 
 int AUD_PLL_APLL ; 
 int AUD_PLL_F1 ; 
 int AUD_PLL_F2 ; 
 int AUD_PLL_HSC0 ; 
 int AUD_PLL_RX0 ; 
 int AUD_PLL_USB0 ; 
 int EINVAL ; 
 int ENOTSUPP ; 
 int SND_SOC_CLOCK_OUT ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned int) ; 
 int find_divider (struct uniphier_aio*,int,unsigned int) ; 
 struct uniphier_aio* uniphier_priv (struct snd_soc_dai*) ; 

__attribute__((used)) static int uniphier_aio_set_sysclk(struct snd_soc_dai *dai, int clk_id,
				   unsigned int freq, int dir)
{
	struct uniphier_aio *aio = uniphier_priv(dai);
	struct device *dev = &aio->chip->pdev->dev;
	bool pll_auto = false;
	int pll_id, div_id;

	switch (clk_id) {
	case AUD_CLK_IO:
		return -ENOTSUPP;
	case AUD_CLK_A1:
		pll_id = AUD_PLL_A1;
		break;
	case AUD_CLK_F1:
		pll_id = AUD_PLL_F1;
		break;
	case AUD_CLK_A2:
		pll_id = AUD_PLL_A2;
		break;
	case AUD_CLK_F2:
		pll_id = AUD_PLL_F2;
		break;
	case AUD_CLK_A:
		pll_id = AUD_PLL_A1;
		pll_auto = true;
		break;
	case AUD_CLK_F:
		pll_id = AUD_PLL_F1;
		pll_auto = true;
		break;
	case AUD_CLK_APLL:
		pll_id = AUD_PLL_APLL;
		break;
	case AUD_CLK_RX0:
		pll_id = AUD_PLL_RX0;
		break;
	case AUD_CLK_USB0:
		pll_id = AUD_PLL_USB0;
		break;
	case AUD_CLK_HSC0:
		pll_id = AUD_PLL_HSC0;
		break;
	default:
		dev_err(dev, "Sysclk(%d) is not supported\n", clk_id);
		return -EINVAL;
	}

	if (pll_auto) {
		for (pll_id = 0; pll_id < aio->chip->num_plls; pll_id++) {
			div_id = find_divider(aio, pll_id, freq);
			if (div_id >= 0) {
				aio->plldiv = div_id;
				break;
			}
		}
		if (pll_id == aio->chip->num_plls) {
			dev_err(dev, "Sysclk frequency is not supported(%d)\n",
				freq);
			return -EINVAL;
		}
	}

	if (dir == SND_SOC_CLOCK_OUT)
		aio->pll_out = pll_id;
	else
		aio->pll_in = pll_id;

	return 0;
}