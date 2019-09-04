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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct uniphier_aio_sub {TYPE_2__* swm; TYPE_4__* aio; } ;
struct regmap {int dummy; } ;
struct TYPE_8__ {TYPE_3__* chip; } ;
struct TYPE_7__ {struct regmap* regmap; } ;
struct TYPE_5__ {int /*<<< orphan*/  map; } ;
struct TYPE_6__ {TYPE_1__ rb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CDA2D_RBMXWRPTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CDA2D_RBMXWRPTRU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CDA2D_WRPTRLOAD ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aiodma_rb_set_wp(struct uniphier_aio_sub *sub, u64 pos)
{
	struct regmap *r = sub->aio->chip->regmap;
	u32 tmp;
	int i;

	regmap_write(r, CDA2D_RBMXWRPTR(sub->swm->rb.map),
		     lower_32_bits(pos));
	regmap_write(r, CDA2D_RBMXWRPTRU(sub->swm->rb.map),
		     upper_32_bits(pos));
	regmap_write(r, CDA2D_WRPTRLOAD, BIT(sub->swm->rb.map));
	/* Wait for setup */
	for (i = 0; i < 6; i++)
		regmap_read(r, CDA2D_RBMXWRPTR(sub->swm->rb.map), &tmp);
}