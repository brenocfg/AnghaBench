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
struct uniphier_aio_sub {TYPE_6__* swm; TYPE_4__* aio; } ;
struct regmap {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  map; } ;
struct TYPE_9__ {int /*<<< orphan*/  map; } ;
struct TYPE_12__ {scalar_t__ dir; TYPE_5__ iport; TYPE_3__ oport; } ;
struct TYPE_10__ {int fmt; TYPE_2__* chip; } ;
struct TYPE_8__ {TYPE_1__* pdev; struct regmap* regmap; } ;
struct TYPE_7__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IPORTMXCTR1 (int /*<<< orphan*/ ) ; 
 int IPORTMXCTR1_CHSEL_ALL ; 
 int IPORTMXCTR1_CHSEL_MASK ; 
 int IPORTMXCTR1_LRSEL_I2S ; 
 int IPORTMXCTR1_LRSEL_LEFT ; 
 int IPORTMXCTR1_LRSEL_MASK ; 
 int IPORTMXCTR1_LRSEL_RIGHT ; 
 int IPORTMXCTR1_OUTBITSEL_24 ; 
 int IPORTMXCTR1_OUTBITSEL_MASK ; 
 int /*<<< orphan*/  OPORTMXCTR1 (int /*<<< orphan*/ ) ; 
 int OPORTMXCTR1_I2SLRSEL_I2S ; 
 int OPORTMXCTR1_I2SLRSEL_LEFT ; 
 int OPORTMXCTR1_I2SLRSEL_MASK ; 
 int OPORTMXCTR1_I2SLRSEL_RIGHT ; 
 int OPORTMXCTR1_OUTBITSEL_24 ; 
 int OPORTMXCTR1_OUTBITSEL_MASK ; 
 scalar_t__ PORT_DIR_OUTPUT ; 
#define  SND_SOC_DAIFMT_I2S 130 
#define  SND_SOC_DAIFMT_LEFT_J 129 
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int aio_port_set_fmt(struct uniphier_aio_sub *sub)
{
	struct regmap *r = sub->aio->chip->regmap;
	struct device *dev = &sub->aio->chip->pdev->dev;
	u32 v;

	if (sub->swm->dir == PORT_DIR_OUTPUT) {
		switch (sub->aio->fmt) {
		case SND_SOC_DAIFMT_LEFT_J:
			v = OPORTMXCTR1_I2SLRSEL_LEFT;
			break;
		case SND_SOC_DAIFMT_RIGHT_J:
			v = OPORTMXCTR1_I2SLRSEL_RIGHT;
			break;
		case SND_SOC_DAIFMT_I2S:
			v = OPORTMXCTR1_I2SLRSEL_I2S;
			break;
		default:
			dev_err(dev, "Format is not supported(%d)\n",
				sub->aio->fmt);
			return -EINVAL;
		}

		v |= OPORTMXCTR1_OUTBITSEL_24;
		regmap_update_bits(r, OPORTMXCTR1(sub->swm->oport.map),
				   OPORTMXCTR1_I2SLRSEL_MASK |
				   OPORTMXCTR1_OUTBITSEL_MASK, v);
	} else {
		switch (sub->aio->fmt) {
		case SND_SOC_DAIFMT_LEFT_J:
			v = IPORTMXCTR1_LRSEL_LEFT;
			break;
		case SND_SOC_DAIFMT_RIGHT_J:
			v = IPORTMXCTR1_LRSEL_RIGHT;
			break;
		case SND_SOC_DAIFMT_I2S:
			v = IPORTMXCTR1_LRSEL_I2S;
			break;
		default:
			dev_err(dev, "Format is not supported(%d)\n",
				sub->aio->fmt);
			return -EINVAL;
		}

		v |= IPORTMXCTR1_OUTBITSEL_24 |
			IPORTMXCTR1_CHSEL_ALL;
		regmap_update_bits(r, IPORTMXCTR1(sub->swm->iport.map),
				   IPORTMXCTR1_LRSEL_MASK |
				   IPORTMXCTR1_OUTBITSEL_MASK |
				   IPORTMXCTR1_CHSEL_MASK, v);
	}

	return 0;
}