#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct uniphier_aio_sub {TYPE_5__* swm; TYPE_2__* aio; } ;
struct regmap {int dummy; } ;
struct TYPE_9__ {int map; } ;
struct TYPE_8__ {int /*<<< orphan*/  map; } ;
struct TYPE_10__ {TYPE_4__ oport; TYPE_3__ iif; } ;
struct TYPE_7__ {TYPE_1__* chip; } ;
struct TYPE_6__ {struct regmap* regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  PBINMXCTR (int /*<<< orphan*/ ) ; 
 int PBINMXCTR_ENDIAN_3210 ; 
 int PBINMXCTR_INOUTSEL_OUT ; 
 int PBINMXCTR_MEMFMT_D0 ; 
 int PBINMXCTR_NCONNECT_CONNECT ; 
 int PBINMXCTR_PBINSEL_SHIFT ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 

int aio_srcif_set_param(struct uniphier_aio_sub *sub)
{
	struct regmap *r = sub->aio->chip->regmap;

	regmap_write(r, PBINMXCTR(sub->swm->iif.map),
		     PBINMXCTR_NCONNECT_CONNECT |
		     PBINMXCTR_INOUTSEL_OUT |
		     (sub->swm->oport.map << PBINMXCTR_PBINSEL_SHIFT) |
		     PBINMXCTR_ENDIAN_3210 |
		     PBINMXCTR_MEMFMT_D0);

	return 0;
}