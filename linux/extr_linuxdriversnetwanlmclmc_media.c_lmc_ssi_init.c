#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_6__ {int cable_type; int /*<<< orphan*/  cardtype; } ;
struct TYPE_7__ {TYPE_1__ ictl; } ;
typedef  TYPE_2__ lmc_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  LMC_CTL_CARDTYPE_LMC1000 ; 
 int /*<<< orphan*/  LMC_GEP_SSI_TXCLOCK ; 
 int LMC_MII17_SSI_CABLE_MASK ; 
 int LMC_MII17_SSI_CABLE_SHIFT ; 
 int /*<<< orphan*/  lmc_gpio_mkoutput (TYPE_2__* const,int /*<<< orphan*/ ) ; 
 int lmc_mii_readreg (TYPE_2__* const,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lmc_ssi_init(lmc_softc_t * const sc)
{
	u16 mii17;
	int cable;

	sc->ictl.cardtype = LMC_CTL_CARDTYPE_LMC1000;

	mii17 = lmc_mii_readreg(sc, 0, 17);

	cable = (mii17 & LMC_MII17_SSI_CABLE_MASK) >> LMC_MII17_SSI_CABLE_SHIFT;
	sc->ictl.cable_type = cable;

	lmc_gpio_mkoutput(sc, LMC_GEP_SSI_TXCLOCK);
}