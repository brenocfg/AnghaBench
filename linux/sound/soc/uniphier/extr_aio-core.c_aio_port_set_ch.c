#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct uniphier_aio_sub {TYPE_2__* swm; int /*<<< orphan*/  params; TYPE_4__* aio; } ;
struct regmap {int dummy; } ;
struct TYPE_8__ {TYPE_3__* chip; } ;
struct TYPE_7__ {struct regmap* regmap; } ;
struct TYPE_5__ {int /*<<< orphan*/  map; } ;
struct TYPE_6__ {TYPE_1__ oport; } ;

/* Variables and functions */
 int AUD_MAX_SLOTSEL ; 
 int EINVAL ; 
 int /*<<< orphan*/  OPORTMXTYSLOTCTR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OPORTMXTYSLOTCTR_MODE ; 
 int /*<<< orphan*/  OPORTMXTYSLOTCTR_SLOTSEL_MASK ; 
 int /*<<< orphan*/  OPORTMXTYSLOTCTR_SLOTSEL_SLOT0 ; 
 int /*<<< orphan*/  OPORTMXTYSLOTCTR_SLOTSEL_SLOT1 ; 
 int /*<<< orphan*/  OPORTMXTYSLOTCTR_SLOTSEL_SLOT2 ; 
 int /*<<< orphan*/  OPORTMXTYSLOTCTR_SLOTSEL_SLOT3 ; 
 int /*<<< orphan*/  OPORTMXTYSLOTCTR_SLOTSEL_SLOT4 ; 
 int params_channels (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aio_port_set_ch(struct uniphier_aio_sub *sub)
{
	struct regmap *r = sub->aio->chip->regmap;
	u32 slotsel_2ch[] = {
		0, 0, 0, 0, 0,
	};
	u32 slotsel_multi[] = {
		OPORTMXTYSLOTCTR_SLOTSEL_SLOT0,
		OPORTMXTYSLOTCTR_SLOTSEL_SLOT1,
		OPORTMXTYSLOTCTR_SLOTSEL_SLOT2,
		OPORTMXTYSLOTCTR_SLOTSEL_SLOT3,
		OPORTMXTYSLOTCTR_SLOTSEL_SLOT4,
	};
	u32 mode, *slotsel;
	int i;

	switch (params_channels(&sub->params)) {
	case 8:
	case 6:
		mode = OPORTMXTYSLOTCTR_MODE;
		slotsel = slotsel_multi;
		break;
	case 2:
		mode = 0;
		slotsel = slotsel_2ch;
		break;
	default:
		return -EINVAL;
	}

	for (i = 0; i < AUD_MAX_SLOTSEL; i++) {
		regmap_update_bits(r, OPORTMXTYSLOTCTR(sub->swm->oport.map, i),
				   OPORTMXTYSLOTCTR_MODE, mode);
		regmap_update_bits(r, OPORTMXTYSLOTCTR(sub->swm->oport.map, i),
				   OPORTMXTYSLOTCTR_SLOTSEL_MASK, slotsel[i]);
	}

	return 0;
}