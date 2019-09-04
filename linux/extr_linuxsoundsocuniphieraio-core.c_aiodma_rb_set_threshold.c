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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct uniphier_aio_sub {TYPE_4__* swm; TYPE_2__* aio; } ;
struct regmap {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  map; } ;
struct TYPE_8__ {TYPE_3__ rb; } ;
struct TYPE_6__ {TYPE_1__* chip; } ;
struct TYPE_5__ {struct regmap* regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDA2D_RBMXBTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CDA2D_RBMXRTH (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,scalar_t__) ; 

int aiodma_rb_set_threshold(struct uniphier_aio_sub *sub, u64 size, u32 th)
{
	struct regmap *r = sub->aio->chip->regmap;

	if (size <= th)
		return -EINVAL;

	regmap_write(r, CDA2D_RBMXBTH(sub->swm->rb.map), th);
	regmap_write(r, CDA2D_RBMXRTH(sub->swm->rb.map), th);

	return 0;
}