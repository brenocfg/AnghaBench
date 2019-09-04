#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int crystalfreq; } ;
struct ssb_chipcommon {TYPE_2__* dev; TYPE_1__ pmu; } ;
struct ssb_bus {int chip_id; } ;
struct pmu0_plltab_entry {int freq; int xf; scalar_t__ wb_frac; scalar_t__ wb_int; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; struct ssb_bus* bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  SSB_CHIPCO_CLKCTLST ; 
 int SSB_CHIPCO_CLKCTLST_HAVEHT ; 
 int /*<<< orphan*/  SSB_CHIPCO_PMU_CTL ; 
 int SSB_CHIPCO_PMU_CTL_ILP_DIV ; 
 int SSB_CHIPCO_PMU_CTL_ILP_DIV_SHIFT ; 
 int SSB_CHIPCO_PMU_CTL_XTALFREQ ; 
 int SSB_CHIPCO_PMU_CTL_XTALFREQ_SHIFT ; 
 int /*<<< orphan*/  SSB_CHIPCO_PMU_MAXRES_MSK ; 
 int /*<<< orphan*/  SSB_CHIPCO_PMU_MINRES_MSK ; 
 int SSB_PMU0_DEFAULT_XTALFREQ ; 
 int /*<<< orphan*/  SSB_PMU0_PLLCTL0 ; 
 int SSB_PMU0_PLLCTL0_PDIV_FREQ ; 
 int SSB_PMU0_PLLCTL0_PDIV_MSK ; 
 int /*<<< orphan*/  SSB_PMU0_PLLCTL1 ; 
 int SSB_PMU0_PLLCTL1_STOPMOD ; 
 int SSB_PMU0_PLLCTL1_WILD_FMSK ; 
 int SSB_PMU0_PLLCTL1_WILD_FMSK_SHIFT ; 
 int SSB_PMU0_PLLCTL1_WILD_IMSK ; 
 int SSB_PMU0_PLLCTL1_WILD_IMSK_SHIFT ; 
 int /*<<< orphan*/  SSB_PMU0_PLLCTL2 ; 
 int SSB_PMU0_PLLCTL2_WILD_IMSKHI ; 
 int SSB_PMU0_PLLCTL2_WILD_IMSKHI_SHIFT ; 
 int SSB_PMURES_4328_BB_PLL_PU ; 
 int SSB_PMURES_5354_BB_PLL_PU ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  chipco_mask32 (struct ssb_chipcommon*,int /*<<< orphan*/ ,int) ; 
 int chipco_read32 (struct ssb_chipcommon*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chipco_write32 (struct ssb_chipcommon*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_emerg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,int) ; 
 struct pmu0_plltab_entry* pmu0_plltab_find_entry (int) ; 
 int ssb_chipco_pll_read (struct ssb_chipcommon*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssb_chipco_pll_write (struct ssb_chipcommon*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ssb_pmu0_pllinit_r0(struct ssb_chipcommon *cc,
				u32 crystalfreq)
{
	struct ssb_bus *bus = cc->dev->bus;
	const struct pmu0_plltab_entry *e = NULL;
	u32 pmuctl, tmp, pllctl;
	unsigned int i;

	if (crystalfreq)
		e = pmu0_plltab_find_entry(crystalfreq);
	if (!e)
		e = pmu0_plltab_find_entry(SSB_PMU0_DEFAULT_XTALFREQ);
	BUG_ON(!e);
	crystalfreq = e->freq;
	cc->pmu.crystalfreq = e->freq;

	/* Check if the PLL already is programmed to this frequency. */
	pmuctl = chipco_read32(cc, SSB_CHIPCO_PMU_CTL);
	if (((pmuctl & SSB_CHIPCO_PMU_CTL_XTALFREQ) >> SSB_CHIPCO_PMU_CTL_XTALFREQ_SHIFT) == e->xf) {
		/* We're already there... */
		return;
	}

	dev_info(cc->dev->dev, "Programming PLL to %u.%03u MHz\n",
		 crystalfreq / 1000, crystalfreq % 1000);

	/* First turn the PLL off. */
	switch (bus->chip_id) {
	case 0x4328:
		chipco_mask32(cc, SSB_CHIPCO_PMU_MINRES_MSK,
			      ~(1 << SSB_PMURES_4328_BB_PLL_PU));
		chipco_mask32(cc, SSB_CHIPCO_PMU_MAXRES_MSK,
			      ~(1 << SSB_PMURES_4328_BB_PLL_PU));
		break;
	case 0x5354:
		chipco_mask32(cc, SSB_CHIPCO_PMU_MINRES_MSK,
			      ~(1 << SSB_PMURES_5354_BB_PLL_PU));
		chipco_mask32(cc, SSB_CHIPCO_PMU_MAXRES_MSK,
			      ~(1 << SSB_PMURES_5354_BB_PLL_PU));
		break;
	default:
		WARN_ON(1);
	}
	for (i = 1500; i; i--) {
		tmp = chipco_read32(cc, SSB_CHIPCO_CLKCTLST);
		if (!(tmp & SSB_CHIPCO_CLKCTLST_HAVEHT))
			break;
		udelay(10);
	}
	tmp = chipco_read32(cc, SSB_CHIPCO_CLKCTLST);
	if (tmp & SSB_CHIPCO_CLKCTLST_HAVEHT)
		dev_emerg(cc->dev->dev, "Failed to turn the PLL off!\n");

	/* Set PDIV in PLL control 0. */
	pllctl = ssb_chipco_pll_read(cc, SSB_PMU0_PLLCTL0);
	if (crystalfreq >= SSB_PMU0_PLLCTL0_PDIV_FREQ)
		pllctl |= SSB_PMU0_PLLCTL0_PDIV_MSK;
	else
		pllctl &= ~SSB_PMU0_PLLCTL0_PDIV_MSK;
	ssb_chipco_pll_write(cc, SSB_PMU0_PLLCTL0, pllctl);

	/* Set WILD in PLL control 1. */
	pllctl = ssb_chipco_pll_read(cc, SSB_PMU0_PLLCTL1);
	pllctl &= ~SSB_PMU0_PLLCTL1_STOPMOD;
	pllctl &= ~(SSB_PMU0_PLLCTL1_WILD_IMSK | SSB_PMU0_PLLCTL1_WILD_FMSK);
	pllctl |= ((u32)e->wb_int << SSB_PMU0_PLLCTL1_WILD_IMSK_SHIFT) & SSB_PMU0_PLLCTL1_WILD_IMSK;
	pllctl |= ((u32)e->wb_frac << SSB_PMU0_PLLCTL1_WILD_FMSK_SHIFT) & SSB_PMU0_PLLCTL1_WILD_FMSK;
	if (e->wb_frac == 0)
		pllctl |= SSB_PMU0_PLLCTL1_STOPMOD;
	ssb_chipco_pll_write(cc, SSB_PMU0_PLLCTL1, pllctl);

	/* Set WILD in PLL control 2. */
	pllctl = ssb_chipco_pll_read(cc, SSB_PMU0_PLLCTL2);
	pllctl &= ~SSB_PMU0_PLLCTL2_WILD_IMSKHI;
	pllctl |= (((u32)e->wb_int >> 4) << SSB_PMU0_PLLCTL2_WILD_IMSKHI_SHIFT) & SSB_PMU0_PLLCTL2_WILD_IMSKHI;
	ssb_chipco_pll_write(cc, SSB_PMU0_PLLCTL2, pllctl);

	/* Set the crystalfrequency and the divisor. */
	pmuctl = chipco_read32(cc, SSB_CHIPCO_PMU_CTL);
	pmuctl &= ~SSB_CHIPCO_PMU_CTL_ILP_DIV;
	pmuctl |= (((crystalfreq + 127) / 128 - 1) << SSB_CHIPCO_PMU_CTL_ILP_DIV_SHIFT)
			& SSB_CHIPCO_PMU_CTL_ILP_DIV;
	pmuctl &= ~SSB_CHIPCO_PMU_CTL_XTALFREQ;
	pmuctl |= ((u32)e->xf << SSB_CHIPCO_PMU_CTL_XTALFREQ_SHIFT) & SSB_CHIPCO_PMU_CTL_XTALFREQ;
	chipco_write32(cc, SSB_CHIPCO_PMU_CTL, pmuctl);
}