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
struct TYPE_8__ {TYPE_3__ och; } ;
struct TYPE_6__ {TYPE_1__* chip; } ;
struct TYPE_5__ {struct regmap* regmap; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CDA2D_STRT0 ; 
 int CDA2D_STRT0_STOP_START ; 
 int CDA2D_STRT0_STOP_STOP ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 

void aio_srcch_set_enable(struct uniphier_aio_sub *sub, int enable)
{
	struct regmap *r = sub->aio->chip->regmap;
	u32 v;

	if (enable)
		v = CDA2D_STRT0_STOP_START;
	else
		v = CDA2D_STRT0_STOP_STOP;

	regmap_write(r, CDA2D_STRT0,
		     v | BIT(sub->swm->och.map));
}