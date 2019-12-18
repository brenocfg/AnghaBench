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
typedef  int /*<<< orphan*/  u32 ;
struct uniphier_aio_sub {TYPE_6__* swm; TYPE_3__* aio; } ;
struct regmap {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  map; } ;
struct TYPE_10__ {int /*<<< orphan*/  map; } ;
struct TYPE_12__ {scalar_t__ dir; TYPE_5__ iport; TYPE_4__ oport; } ;
struct TYPE_9__ {TYPE_2__* chip; } ;
struct TYPE_8__ {TYPE_1__* pdev; struct regmap* regmap; } ;
struct TYPE_7__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IPORTMXCTR1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPORTMXCTR1_FSSEL_11_025 ; 
 int /*<<< orphan*/  IPORTMXCTR1_FSSEL_12 ; 
 int /*<<< orphan*/  IPORTMXCTR1_FSSEL_16 ; 
 int /*<<< orphan*/  IPORTMXCTR1_FSSEL_176_4 ; 
 int /*<<< orphan*/  IPORTMXCTR1_FSSEL_192 ; 
 int /*<<< orphan*/  IPORTMXCTR1_FSSEL_22_05 ; 
 int /*<<< orphan*/  IPORTMXCTR1_FSSEL_24 ; 
 int /*<<< orphan*/  IPORTMXCTR1_FSSEL_32 ; 
 int /*<<< orphan*/  IPORTMXCTR1_FSSEL_44_1 ; 
 int /*<<< orphan*/  IPORTMXCTR1_FSSEL_48 ; 
 int /*<<< orphan*/  IPORTMXCTR1_FSSEL_8 ; 
 int /*<<< orphan*/  IPORTMXCTR1_FSSEL_88_2 ; 
 int /*<<< orphan*/  IPORTMXCTR1_FSSEL_96 ; 
 int /*<<< orphan*/  IPORTMXCTR1_FSSEL_MASK ; 
 int /*<<< orphan*/  OPORTMXCTR1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPORTMXCTR1_FSSEL_11_025 ; 
 int /*<<< orphan*/  OPORTMXCTR1_FSSEL_12 ; 
 int /*<<< orphan*/  OPORTMXCTR1_FSSEL_16 ; 
 int /*<<< orphan*/  OPORTMXCTR1_FSSEL_176_4 ; 
 int /*<<< orphan*/  OPORTMXCTR1_FSSEL_192 ; 
 int /*<<< orphan*/  OPORTMXCTR1_FSSEL_22_05 ; 
 int /*<<< orphan*/  OPORTMXCTR1_FSSEL_24 ; 
 int /*<<< orphan*/  OPORTMXCTR1_FSSEL_32 ; 
 int /*<<< orphan*/  OPORTMXCTR1_FSSEL_44_1 ; 
 int /*<<< orphan*/  OPORTMXCTR1_FSSEL_48 ; 
 int /*<<< orphan*/  OPORTMXCTR1_FSSEL_8 ; 
 int /*<<< orphan*/  OPORTMXCTR1_FSSEL_88_2 ; 
 int /*<<< orphan*/  OPORTMXCTR1_FSSEL_96 ; 
 int /*<<< orphan*/  OPORTMXCTR1_FSSEL_MASK ; 
 scalar_t__ PORT_DIR_OUTPUT ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aio_port_set_rate(struct uniphier_aio_sub *sub, int rate)
{
	struct regmap *r = sub->aio->chip->regmap;
	struct device *dev = &sub->aio->chip->pdev->dev;
	u32 v;

	if (sub->swm->dir == PORT_DIR_OUTPUT) {
		switch (rate) {
		case 8000:
			v = OPORTMXCTR1_FSSEL_8;
			break;
		case 11025:
			v = OPORTMXCTR1_FSSEL_11_025;
			break;
		case 12000:
			v = OPORTMXCTR1_FSSEL_12;
			break;
		case 16000:
			v = OPORTMXCTR1_FSSEL_16;
			break;
		case 22050:
			v = OPORTMXCTR1_FSSEL_22_05;
			break;
		case 24000:
			v = OPORTMXCTR1_FSSEL_24;
			break;
		case 32000:
			v = OPORTMXCTR1_FSSEL_32;
			break;
		case 44100:
			v = OPORTMXCTR1_FSSEL_44_1;
			break;
		case 48000:
			v = OPORTMXCTR1_FSSEL_48;
			break;
		case 88200:
			v = OPORTMXCTR1_FSSEL_88_2;
			break;
		case 96000:
			v = OPORTMXCTR1_FSSEL_96;
			break;
		case 176400:
			v = OPORTMXCTR1_FSSEL_176_4;
			break;
		case 192000:
			v = OPORTMXCTR1_FSSEL_192;
			break;
		default:
			dev_err(dev, "Rate not supported(%d)\n", rate);
			return -EINVAL;
		}

		regmap_update_bits(r, OPORTMXCTR1(sub->swm->oport.map),
				   OPORTMXCTR1_FSSEL_MASK, v);
	} else {
		switch (rate) {
		case 8000:
			v = IPORTMXCTR1_FSSEL_8;
			break;
		case 11025:
			v = IPORTMXCTR1_FSSEL_11_025;
			break;
		case 12000:
			v = IPORTMXCTR1_FSSEL_12;
			break;
		case 16000:
			v = IPORTMXCTR1_FSSEL_16;
			break;
		case 22050:
			v = IPORTMXCTR1_FSSEL_22_05;
			break;
		case 24000:
			v = IPORTMXCTR1_FSSEL_24;
			break;
		case 32000:
			v = IPORTMXCTR1_FSSEL_32;
			break;
		case 44100:
			v = IPORTMXCTR1_FSSEL_44_1;
			break;
		case 48000:
			v = IPORTMXCTR1_FSSEL_48;
			break;
		case 88200:
			v = IPORTMXCTR1_FSSEL_88_2;
			break;
		case 96000:
			v = IPORTMXCTR1_FSSEL_96;
			break;
		case 176400:
			v = IPORTMXCTR1_FSSEL_176_4;
			break;
		case 192000:
			v = IPORTMXCTR1_FSSEL_192;
			break;
		default:
			dev_err(dev, "Rate not supported(%d)\n", rate);
			return -EINVAL;
		}

		regmap_update_bits(r, IPORTMXCTR1(sub->swm->iport.map),
				   IPORTMXCTR1_FSSEL_MASK, v);
	}

	return 0;
}