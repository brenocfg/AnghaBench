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
typedef  int u32 ;
struct uniphier_aio_sub {TYPE_4__* swm; TYPE_2__* aio; } ;
struct regmap {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  map; } ;
struct TYPE_8__ {scalar_t__ dir; TYPE_3__ rb; } ;
struct TYPE_6__ {TYPE_1__* chip; } ;
struct TYPE_5__ {struct regmap* regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDA2D_RBMXIR (int /*<<< orphan*/ ) ; 
 int CDA2D_RBMXIX_REMAIN ; 
 int CDA2D_RBMXIX_SPACE ; 
 scalar_t__ PORT_DIR_OUTPUT ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,int*) ; 

bool aiodma_rb_is_irq(struct uniphier_aio_sub *sub)
{
	struct regmap *r = sub->aio->chip->regmap;
	u32 ir;

	regmap_read(r, CDA2D_RBMXIR(sub->swm->rb.map), &ir);

	if (sub->swm->dir == PORT_DIR_OUTPUT)
		return !!(ir & CDA2D_RBMXIX_SPACE);
	else
		return !!(ir & CDA2D_RBMXIX_REMAIN);
}