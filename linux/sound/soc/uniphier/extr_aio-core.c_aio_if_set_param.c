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
struct uniphier_aio_sub {TYPE_6__* swm; int /*<<< orphan*/  params; TYPE_2__* aio; } ;
struct regmap {int dummy; } ;
struct TYPE_11__ {int map; } ;
struct TYPE_10__ {int /*<<< orphan*/  map; } ;
struct TYPE_9__ {int /*<<< orphan*/  map; } ;
struct TYPE_12__ {scalar_t__ dir; TYPE_5__ iport; TYPE_4__ iif; TYPE_3__ oif; } ;
struct TYPE_8__ {TYPE_1__* chip; } ;
struct TYPE_7__ {struct regmap* regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PBINMXCTR (int /*<<< orphan*/ ) ; 
 int PBINMXCTR_ENDIAN_3210 ; 
 int PBINMXCTR_INOUTSEL_IN ; 
 int PBINMXCTR_MEMFMT_D0 ; 
 int PBINMXCTR_NCONNECT_CONNECT ; 
 int PBINMXCTR_PBINSEL_SHIFT ; 
 int /*<<< orphan*/  PBOUTMXCTR0 (int /*<<< orphan*/ ) ; 
 int PBOUTMXCTR0_ENDIAN_0123 ; 
 int PBOUTMXCTR0_ENDIAN_3210 ; 
 int PBOUTMXCTR0_MEMFMT_2CH ; 
 int PBOUTMXCTR0_MEMFMT_6CH ; 
 int PBOUTMXCTR0_MEMFMT_8CH ; 
 int PBOUTMXCTR0_MEMFMT_STREAM ; 
 int /*<<< orphan*/  PBOUTMXCTR1 (int /*<<< orphan*/ ) ; 
 scalar_t__ PORT_DIR_OUTPUT ; 
 int params_channels (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 

int aio_if_set_param(struct uniphier_aio_sub *sub, int pass_through)
{
	struct regmap *r = sub->aio->chip->regmap;
	u32 memfmt, v;

	if (sub->swm->dir == PORT_DIR_OUTPUT) {
		if (pass_through) {
			v = PBOUTMXCTR0_ENDIAN_0123 |
				PBOUTMXCTR0_MEMFMT_STREAM;
		} else {
			switch (params_channels(&sub->params)) {
			case 2:
				memfmt = PBOUTMXCTR0_MEMFMT_2CH;
				break;
			case 6:
				memfmt = PBOUTMXCTR0_MEMFMT_6CH;
				break;
			case 8:
				memfmt = PBOUTMXCTR0_MEMFMT_8CH;
				break;
			default:
				return -EINVAL;
			}
			v = PBOUTMXCTR0_ENDIAN_3210 | memfmt;
		}

		regmap_write(r, PBOUTMXCTR0(sub->swm->oif.map), v);
		regmap_write(r, PBOUTMXCTR1(sub->swm->oif.map), 0);
	} else {
		regmap_write(r, PBINMXCTR(sub->swm->iif.map),
			     PBINMXCTR_NCONNECT_CONNECT |
			     PBINMXCTR_INOUTSEL_IN |
			     (sub->swm->iport.map << PBINMXCTR_PBINSEL_SHIFT) |
			     PBINMXCTR_ENDIAN_3210 |
			     PBINMXCTR_MEMFMT_D0);
	}

	return 0;
}