#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ antswlut; int /*<<< orphan*/  tr_iso; int /*<<< orphan*/  pdet_range; int /*<<< orphan*/  extpa_gain; int /*<<< orphan*/  tssipos; } ;
struct TYPE_11__ {scalar_t__ antswlut; int /*<<< orphan*/  tr_iso; int /*<<< orphan*/  pdet_range; int /*<<< orphan*/  extpa_gain; int /*<<< orphan*/  tssipos; } ;
struct TYPE_14__ {TYPE_6__ ghz2; TYPE_4__ ghz5; } ;
struct ssb_sprom {scalar_t__ tempthresh; scalar_t__ tempoffset; scalar_t__ phycal_tempdelta; TYPE_7__ fem; int /*<<< orphan*/  ant_available_a; int /*<<< orphan*/  ant_available_bg; int /*<<< orphan*/  antswitch; } ;
struct TYPE_12__ {scalar_t__ antswctrllut; int /*<<< orphan*/  triso; int /*<<< orphan*/  pdetrange; int /*<<< orphan*/  extpagain; int /*<<< orphan*/  tssipos; } ;
struct TYPE_10__ {scalar_t__ antswctrllut; int /*<<< orphan*/  triso; int /*<<< orphan*/  pdetrange; int /*<<< orphan*/  extpagain; int /*<<< orphan*/  tssipos; } ;
struct brcms_phy {scalar_t__ phy_txcore_disable_temp; scalar_t__ phy_tempsense_offset; scalar_t__ phy_txcore_enable_temp; scalar_t__ phycal_tempdelta; TYPE_5__ srom_fem5g; TYPE_3__ srom_fem2g; int /*<<< orphan*/  aa5g; int /*<<< orphan*/  aa2g; int /*<<< orphan*/  antswitch; TYPE_2__* d11core; } ;
struct TYPE_9__ {TYPE_1__* bus; } ;
struct TYPE_8__ {struct ssb_sprom sprom; } ;

/* Variables and functions */
 scalar_t__ NPHY_CAL_MAXTEMPDELTA ; 
 scalar_t__ NPHY_SROM_MAXTEMPOFFSET ; 
 scalar_t__ NPHY_SROM_MINTEMPOFFSET ; 
 scalar_t__ NPHY_SROM_TEMPSHIFT ; 
 scalar_t__ PHY_CHAIN_TX_DISABLE_TEMP ; 
 scalar_t__ PHY_HYSTERESIS_DELTATEMP ; 
 int /*<<< orphan*/  wlc_phy_txpower_ipa_upd (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_txpwr_srom_read_ppr_nphy (struct brcms_phy*) ; 

__attribute__((used)) static bool wlc_phy_txpwr_srom_read_nphy(struct brcms_phy *pi)
{
	struct ssb_sprom *sprom = &pi->d11core->bus->sprom;

	pi->antswitch = sprom->antswitch;
	pi->aa2g = sprom->ant_available_bg;
	pi->aa5g = sprom->ant_available_a;

	pi->srom_fem2g.tssipos = sprom->fem.ghz2.tssipos;
	pi->srom_fem2g.extpagain = sprom->fem.ghz2.extpa_gain;
	pi->srom_fem2g.pdetrange = sprom->fem.ghz2.pdet_range;
	pi->srom_fem2g.triso = sprom->fem.ghz2.tr_iso;
	pi->srom_fem2g.antswctrllut = sprom->fem.ghz2.antswlut;

	pi->srom_fem5g.tssipos = sprom->fem.ghz5.tssipos;
	pi->srom_fem5g.extpagain = sprom->fem.ghz5.extpa_gain;
	pi->srom_fem5g.pdetrange = sprom->fem.ghz5.pdet_range;
	pi->srom_fem5g.triso = sprom->fem.ghz5.tr_iso;
	if (sprom->fem.ghz5.antswlut)
		pi->srom_fem5g.antswctrllut = sprom->fem.ghz5.antswlut;
	else
		pi->srom_fem5g.antswctrllut = sprom->fem.ghz2.antswlut;

	wlc_phy_txpower_ipa_upd(pi);

	pi->phy_txcore_disable_temp = sprom->tempthresh;
	if (pi->phy_txcore_disable_temp == 0)
		pi->phy_txcore_disable_temp = PHY_CHAIN_TX_DISABLE_TEMP;

	pi->phy_tempsense_offset = sprom->tempoffset;
	if (pi->phy_tempsense_offset != 0) {
		if (pi->phy_tempsense_offset >
		    (NPHY_SROM_TEMPSHIFT + NPHY_SROM_MAXTEMPOFFSET))
			pi->phy_tempsense_offset = NPHY_SROM_MAXTEMPOFFSET;
		else if (pi->phy_tempsense_offset < (NPHY_SROM_TEMPSHIFT +
						     NPHY_SROM_MINTEMPOFFSET))
			pi->phy_tempsense_offset = NPHY_SROM_MINTEMPOFFSET;
		else
			pi->phy_tempsense_offset -= NPHY_SROM_TEMPSHIFT;
	}

	pi->phy_txcore_enable_temp =
		pi->phy_txcore_disable_temp - PHY_HYSTERESIS_DELTATEMP;

	pi->phycal_tempdelta = sprom->phycal_tempdelta;
	if (pi->phycal_tempdelta > NPHY_CAL_MAXTEMPDELTA)
		pi->phycal_tempdelta = 0;

	wlc_phy_txpwr_srom_read_ppr_nphy(pi);

	return true;
}