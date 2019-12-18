#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct uniphier_aio_sub {TYPE_11__* swm; TYPE_3__* aio; } ;
struct regmap {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_22__ {int map; int /*<<< orphan*/  hw; } ;
struct TYPE_21__ {int map; int /*<<< orphan*/  hw; } ;
struct TYPE_20__ {int map; int /*<<< orphan*/  hw; } ;
struct TYPE_19__ {int map; int /*<<< orphan*/  hw; } ;
struct TYPE_18__ {int map; int /*<<< orphan*/  hw; } ;
struct TYPE_17__ {int map; int /*<<< orphan*/  hw; } ;
struct TYPE_16__ {TYPE_2__* chip; } ;
struct TYPE_15__ {struct regmap* regmap; TYPE_1__* pdev; } ;
struct TYPE_14__ {struct device dev; } ;
struct TYPE_12__ {int map; int /*<<< orphan*/  hw; } ;
struct TYPE_13__ {int type; TYPE_10__ iif; TYPE_9__ och; TYPE_8__ oport; TYPE_7__ oif; TYPE_6__ iport; int /*<<< orphan*/  dir; TYPE_5__ ch; TYPE_4__ rb; } ;

/* Variables and functions */
 int /*<<< orphan*/  A2CHNMAPCTR0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  A2IIFNMAPCTR0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  A2IPORTNMAPCTR0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  A2OIFNMAPCTR0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  A2OPORTNMAPCTR0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  A2RBNMAPCTR0 (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int MAPCTR0_EN ; 
 int /*<<< orphan*/  PORT_DIR_INPUT ; 
#define  PORT_TYPE_CONV 131 
#define  PORT_TYPE_EVE 130 
#define  PORT_TYPE_I2S 129 
#define  PORT_TYPE_SPDIF 128 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 

int aio_init(struct uniphier_aio_sub *sub)
{
	struct device *dev = &sub->aio->chip->pdev->dev;
	struct regmap *r = sub->aio->chip->regmap;

	regmap_write(r, A2RBNMAPCTR0(sub->swm->rb.hw),
		     MAPCTR0_EN | sub->swm->rb.map);
	regmap_write(r, A2CHNMAPCTR0(sub->swm->ch.hw),
		     MAPCTR0_EN | sub->swm->ch.map);

	switch (sub->swm->type) {
	case PORT_TYPE_I2S:
	case PORT_TYPE_SPDIF:
	case PORT_TYPE_EVE:
		if (sub->swm->dir == PORT_DIR_INPUT) {
			regmap_write(r, A2IIFNMAPCTR0(sub->swm->iif.hw),
				     MAPCTR0_EN | sub->swm->iif.map);
			regmap_write(r, A2IPORTNMAPCTR0(sub->swm->iport.hw),
				     MAPCTR0_EN | sub->swm->iport.map);
		} else {
			regmap_write(r, A2OIFNMAPCTR0(sub->swm->oif.hw),
				     MAPCTR0_EN | sub->swm->oif.map);
			regmap_write(r, A2OPORTNMAPCTR0(sub->swm->oport.hw),
				     MAPCTR0_EN | sub->swm->oport.map);
		}
		break;
	case PORT_TYPE_CONV:
		regmap_write(r, A2OIFNMAPCTR0(sub->swm->oif.hw),
			     MAPCTR0_EN | sub->swm->oif.map);
		regmap_write(r, A2OPORTNMAPCTR0(sub->swm->oport.hw),
			     MAPCTR0_EN | sub->swm->oport.map);
		regmap_write(r, A2CHNMAPCTR0(sub->swm->och.hw),
			     MAPCTR0_EN | sub->swm->och.map);
		regmap_write(r, A2IIFNMAPCTR0(sub->swm->iif.hw),
			     MAPCTR0_EN | sub->swm->iif.map);
		break;
	default:
		dev_err(dev, "Unknown port type %d.\n", sub->swm->type);
		return -EINVAL;
	}

	return 0;
}