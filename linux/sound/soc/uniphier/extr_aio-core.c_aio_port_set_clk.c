#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct uniphier_aio_sub {TYPE_6__* swm; TYPE_3__* aio; } ;
struct uniphier_aio_chip {TYPE_2__* plls; struct regmap* regmap; TYPE_1__* pdev; } ;
struct regmap {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  map; } ;
struct TYPE_10__ {int /*<<< orphan*/  map; } ;
struct TYPE_12__ {scalar_t__ dir; scalar_t__ type; TYPE_5__ iport; TYPE_4__ oport; } ;
struct TYPE_9__ {size_t pll_out; size_t plldiv; struct uniphier_aio_chip* chip; } ;
struct TYPE_8__ {int freq; } ;
struct TYPE_7__ {struct device dev; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  IPORTMXCTR2 (int /*<<< orphan*/ ) ; 
 int IPORTMXCTR2_ACLKSEL_A1 ; 
 int IPORTMXCTR2_DACCKSEL_1_2 ; 
 int IPORTMXCTR2_EXTLSIFSSEL_36 ; 
 int IPORTMXCTR2_MSSEL_SLAVE ; 
 int /*<<< orphan*/  OPORTMXCTR2 (int /*<<< orphan*/ ) ; 
 int OPORTMXCTR2_ACLKSEL_A1 ; 
 int OPORTMXCTR2_ACLKSEL_A2 ; 
 int OPORTMXCTR2_ACLKSEL_A2PLL ; 
 int OPORTMXCTR2_ACLKSEL_F1 ; 
 int OPORTMXCTR2_ACLKSEL_F2 ; 
 int OPORTMXCTR2_ACLKSEL_RX1 ; 
 int OPORTMXCTR2_DACCKSEL_1_1 ; 
 int OPORTMXCTR2_DACCKSEL_1_2 ; 
 int OPORTMXCTR2_DACCKSEL_1_3 ; 
 int OPORTMXCTR2_DACCKSEL_2_3 ; 
 int OPORTMXCTR2_EXTLSIFSSEL_24 ; 
 int OPORTMXCTR2_EXTLSIFSSEL_36 ; 
 int OPORTMXCTR2_MSSEL_MASTER ; 
 scalar_t__ PORT_DIR_OUTPUT ; 
 scalar_t__ PORT_TYPE_EVE ; 
 scalar_t__ PORT_TYPE_I2S ; 
 scalar_t__ PORT_TYPE_SPDIF ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,size_t) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int aio_port_set_clk(struct uniphier_aio_sub *sub)
{
	struct uniphier_aio_chip *chip = sub->aio->chip;
	struct device *dev = &sub->aio->chip->pdev->dev;
	struct regmap *r = sub->aio->chip->regmap;
	u32 v_pll[] = {
		OPORTMXCTR2_ACLKSEL_A1, OPORTMXCTR2_ACLKSEL_F1,
		OPORTMXCTR2_ACLKSEL_A2, OPORTMXCTR2_ACLKSEL_F2,
		OPORTMXCTR2_ACLKSEL_A2PLL,
		OPORTMXCTR2_ACLKSEL_RX1,
	};
	u32 v_div[] = {
		OPORTMXCTR2_DACCKSEL_1_2, OPORTMXCTR2_DACCKSEL_1_3,
		OPORTMXCTR2_DACCKSEL_1_1, OPORTMXCTR2_DACCKSEL_2_3,
	};
	u32 v;

	if (sub->swm->dir == PORT_DIR_OUTPUT) {
		if (sub->swm->type == PORT_TYPE_I2S) {
			if (sub->aio->pll_out >= ARRAY_SIZE(v_pll)) {
				dev_err(dev, "PLL(%d) is invalid\n",
					sub->aio->pll_out);
				return -EINVAL;
			}
			if (sub->aio->plldiv >= ARRAY_SIZE(v_div)) {
				dev_err(dev, "PLL divider(%d) is invalid\n",
					sub->aio->plldiv);
				return -EINVAL;
			}

			v = v_pll[sub->aio->pll_out] |
				OPORTMXCTR2_MSSEL_MASTER |
				v_div[sub->aio->plldiv];

			switch (chip->plls[sub->aio->pll_out].freq) {
			case 0:
			case 36864000:
			case 33868800:
				v |= OPORTMXCTR2_EXTLSIFSSEL_36;
				break;
			default:
				v |= OPORTMXCTR2_EXTLSIFSSEL_24;
				break;
			}
		} else if (sub->swm->type == PORT_TYPE_EVE) {
			v = OPORTMXCTR2_ACLKSEL_A2PLL |
				OPORTMXCTR2_MSSEL_MASTER |
				OPORTMXCTR2_EXTLSIFSSEL_36 |
				OPORTMXCTR2_DACCKSEL_1_2;
		} else if (sub->swm->type == PORT_TYPE_SPDIF) {
			if (sub->aio->pll_out >= ARRAY_SIZE(v_pll)) {
				dev_err(dev, "PLL(%d) is invalid\n",
					sub->aio->pll_out);
				return -EINVAL;
			}
			v = v_pll[sub->aio->pll_out] |
				OPORTMXCTR2_MSSEL_MASTER |
				OPORTMXCTR2_DACCKSEL_1_2;

			switch (chip->plls[sub->aio->pll_out].freq) {
			case 0:
			case 36864000:
			case 33868800:
				v |= OPORTMXCTR2_EXTLSIFSSEL_36;
				break;
			default:
				v |= OPORTMXCTR2_EXTLSIFSSEL_24;
				break;
			}
		} else {
			v = OPORTMXCTR2_ACLKSEL_A1 |
				OPORTMXCTR2_MSSEL_MASTER |
				OPORTMXCTR2_EXTLSIFSSEL_36 |
				OPORTMXCTR2_DACCKSEL_1_2;
		}
		regmap_write(r, OPORTMXCTR2(sub->swm->oport.map), v);
	} else {
		v = IPORTMXCTR2_ACLKSEL_A1 |
			IPORTMXCTR2_MSSEL_SLAVE |
			IPORTMXCTR2_EXTLSIFSSEL_36 |
			IPORTMXCTR2_DACCKSEL_1_2;
		regmap_write(r, IPORTMXCTR2(sub->swm->iport.map), v);
	}

	return 0;
}