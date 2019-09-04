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
struct uniphier_aio_sub {TYPE_3__* swm; TYPE_2__* aio; } ;
struct regmap {int dummy; } ;
struct TYPE_8__ {int map; } ;
struct TYPE_7__ {TYPE_4__ och; } ;
struct TYPE_6__ {TYPE_1__* chip; } ;
struct TYPE_5__ {struct regmap* regmap; } ;

/* Variables and functions */
 int CDA2D_CHMXAMODE_AUPDT_FIX ; 
 int CDA2D_CHMXAMODE_AUPDT_INC ; 
 int CDA2D_CHMXAMODE_ENDIAN_3210 ; 
 int CDA2D_CHMXAMODE_RSSEL_SHIFT ; 
 int CDA2D_CHMXAMODE_TYPE_NORMAL ; 
 int CDA2D_CHMXAMODE_TYPE_RING ; 
 int /*<<< orphan*/  CDA2D_CHMXCTRL1 (int) ; 
 int CDA2D_CHMXCTRL1_INDSIZE_INFINITE ; 
 int /*<<< orphan*/  CDA2D_CHMXDSTAMODE (int) ; 
 int /*<<< orphan*/  CDA2D_CHMXSRCAMODE (int) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 

int aio_srcch_set_param(struct uniphier_aio_sub *sub)
{
	struct regmap *r = sub->aio->chip->regmap;

	regmap_write(r, CDA2D_CHMXCTRL1(sub->swm->och.map),
		     CDA2D_CHMXCTRL1_INDSIZE_INFINITE);

	regmap_write(r, CDA2D_CHMXSRCAMODE(sub->swm->och.map),
		     CDA2D_CHMXAMODE_ENDIAN_3210 |
		     CDA2D_CHMXAMODE_AUPDT_FIX |
		     CDA2D_CHMXAMODE_TYPE_NORMAL);

	regmap_write(r, CDA2D_CHMXDSTAMODE(sub->swm->och.map),
		     CDA2D_CHMXAMODE_ENDIAN_3210 |
		     CDA2D_CHMXAMODE_AUPDT_INC |
		     CDA2D_CHMXAMODE_TYPE_RING |
		     (sub->swm->och.map << CDA2D_CHMXAMODE_RSSEL_SHIFT));

	return 0;
}