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
typedef  int u64 ;
typedef  int u32 ;
struct uniphier_aio_sub {TYPE_4__* swm; TYPE_2__* aio; } ;
struct regmap {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  map; } ;
struct TYPE_8__ {TYPE_3__ rb; } ;
struct TYPE_6__ {TYPE_1__* chip; } ;
struct TYPE_5__ {struct regmap* regmap; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CDA2D_RBMXPTRU_PTRU_MASK ; 
 int /*<<< orphan*/  CDA2D_RBMXWRPTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CDA2D_RBMXWRPTRU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CDA2D_WRPTRLOAD ; 
 int CDA2D_WRPTRLOAD_LSFLAG_STORE ; 
 int FIELD_GET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u64 aiodma_rb_get_wp(struct uniphier_aio_sub *sub)
{
	struct regmap *r = sub->aio->chip->regmap;
	u32 pos_u, pos_l;
	int i;

	regmap_write(r, CDA2D_WRPTRLOAD,
		     CDA2D_WRPTRLOAD_LSFLAG_STORE | BIT(sub->swm->rb.map));
	/* Wait for setup */
	for (i = 0; i < 6; i++)
		regmap_read(r, CDA2D_RBMXWRPTR(sub->swm->rb.map), &pos_l);

	regmap_read(r, CDA2D_RBMXWRPTR(sub->swm->rb.map), &pos_l);
	regmap_read(r, CDA2D_RBMXWRPTRU(sub->swm->rb.map), &pos_u);
	pos_u = FIELD_GET(CDA2D_RBMXPTRU_PTRU_MASK, pos_u);

	return ((u64)pos_u << 32) | pos_l;
}