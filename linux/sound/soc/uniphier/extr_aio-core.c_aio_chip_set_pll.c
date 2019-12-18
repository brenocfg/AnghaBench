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
typedef  int u32 ;
struct uniphier_aio_chip {TYPE_1__* plls; struct regmap* regmap; TYPE_2__* pdev; } ;
struct regmap {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct device dev; } ;
struct TYPE_3__ {unsigned int freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  A2APLLCTR1 ; 
 int A2APLLCTR1_APLLX_33MHZ ; 
 int A2APLLCTR1_APLLX_36MHZ ; 
 int A2APLLCTR1_APLLX_MASK ; 
#define  AUD_PLL_A1 131 
#define  AUD_PLL_A2 130 
#define  AUD_PLL_F1 129 
#define  AUD_PLL_F2 128 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned int) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int,int) ; 

int aio_chip_set_pll(struct uniphier_aio_chip *chip, int pll_id,
		     unsigned int freq)
{
	struct device *dev = &chip->pdev->dev;
	struct regmap *r = chip->regmap;
	int shift;
	u32 v;

	/* Not change */
	if (freq == 0)
		return 0;

	switch (pll_id) {
	case AUD_PLL_A1:
		shift = 0;
		break;
	case AUD_PLL_F1:
		shift = 1;
		break;
	case AUD_PLL_A2:
		shift = 2;
		break;
	case AUD_PLL_F2:
		shift = 3;
		break;
	default:
		dev_err(dev, "PLL(%d) not supported\n", pll_id);
		return -EINVAL;
	}

	switch (freq) {
	case 36864000:
		v = A2APLLCTR1_APLLX_36MHZ;
		break;
	case 33868800:
		v = A2APLLCTR1_APLLX_33MHZ;
		break;
	default:
		dev_err(dev, "PLL frequency not supported(%d)\n", freq);
		return -EINVAL;
	}
	chip->plls[pll_id].freq = freq;

	regmap_update_bits(r, A2APLLCTR1, A2APLLCTR1_APLLX_MASK << shift,
			   v << shift);

	return 0;
}