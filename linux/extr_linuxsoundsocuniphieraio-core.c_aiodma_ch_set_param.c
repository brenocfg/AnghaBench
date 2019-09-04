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
typedef  int u32 ;
struct uniphier_aio_sub {TYPE_3__* swm; TYPE_5__* aio; } ;
struct regmap {int dummy; } ;
struct TYPE_10__ {TYPE_4__* chip; } ;
struct TYPE_9__ {struct regmap* regmap; } ;
struct TYPE_7__ {int /*<<< orphan*/  map; } ;
struct TYPE_6__ {int map; } ;
struct TYPE_8__ {scalar_t__ dir; TYPE_2__ ch; TYPE_1__ rb; } ;

/* Variables and functions */
 int CDA2D_CHMXAMODE_AUPDT_INC ; 
 int CDA2D_CHMXAMODE_ENDIAN_3210 ; 
 int CDA2D_CHMXAMODE_RSSEL_SHIFT ; 
 int CDA2D_CHMXAMODE_TYPE_NORMAL ; 
 int /*<<< orphan*/  CDA2D_CHMXCTRL1 (int /*<<< orphan*/ ) ; 
 int CDA2D_CHMXCTRL1_INDSIZE_INFINITE ; 
 int /*<<< orphan*/  CDA2D_CHMXDSTAMODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CDA2D_CHMXSRCAMODE (int /*<<< orphan*/ ) ; 
 scalar_t__ PORT_DIR_OUTPUT ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 

int aiodma_ch_set_param(struct uniphier_aio_sub *sub)
{
	struct regmap *r = sub->aio->chip->regmap;
	u32 v;

	regmap_write(r, CDA2D_CHMXCTRL1(sub->swm->ch.map),
		     CDA2D_CHMXCTRL1_INDSIZE_INFINITE);

	v = CDA2D_CHMXAMODE_ENDIAN_3210 |
		CDA2D_CHMXAMODE_AUPDT_INC |
		CDA2D_CHMXAMODE_TYPE_NORMAL |
		(sub->swm->rb.map << CDA2D_CHMXAMODE_RSSEL_SHIFT);
	if (sub->swm->dir == PORT_DIR_OUTPUT)
		regmap_write(r, CDA2D_CHMXSRCAMODE(sub->swm->ch.map), v);
	else
		regmap_write(r, CDA2D_CHMXDSTAMODE(sub->swm->ch.map), v);

	return 0;
}