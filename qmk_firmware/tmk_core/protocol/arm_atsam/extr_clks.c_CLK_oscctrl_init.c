#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_46__   TYPE_9__ ;
typedef  struct TYPE_45__   TYPE_8__ ;
typedef  struct TYPE_44__   TYPE_7__ ;
typedef  struct TYPE_43__   TYPE_6__ ;
typedef  struct TYPE_42__   TYPE_5__ ;
typedef  struct TYPE_41__   TYPE_4__ ;
typedef  struct TYPE_40__   TYPE_3__ ;
typedef  struct TYPE_39__   TYPE_2__ ;
typedef  struct TYPE_38__   TYPE_22__ ;
typedef  struct TYPE_37__   TYPE_21__ ;
typedef  struct TYPE_36__   TYPE_20__ ;
typedef  struct TYPE_35__   TYPE_1__ ;
typedef  struct TYPE_34__   TYPE_19__ ;
typedef  struct TYPE_33__   TYPE_18__ ;
typedef  struct TYPE_32__   TYPE_17__ ;
typedef  struct TYPE_31__   TYPE_16__ ;
typedef  struct TYPE_30__   TYPE_15__ ;
typedef  struct TYPE_29__   TYPE_14__ ;
typedef  struct TYPE_28__   TYPE_13__ ;
typedef  struct TYPE_27__   TYPE_12__ ;
typedef  struct TYPE_26__   TYPE_11__ ;
typedef  struct TYPE_25__   TYPE_10__ ;

/* Type definitions */
struct TYPE_46__ {scalar_t__ LOCK; scalar_t__ CLKRDY; } ;
struct TYPE_44__ {scalar_t__ ENABLE; scalar_t__ DPLLRATIO; } ;
struct TYPE_45__ {TYPE_7__ bit; } ;
struct TYPE_42__ {int ENABLE; scalar_t__ ONDEMAND; } ;
struct TYPE_43__ {TYPE_5__ bit; } ;
struct TYPE_40__ {scalar_t__ XOSCRDY0; } ;
struct TYPE_41__ {TYPE_3__ bit; } ;
struct TYPE_35__ {int ENABLE; int STARTUP; int ENALC; int IMULT; int IPTAT; int XTALEN; scalar_t__ ONDEMAND; } ;
struct TYPE_39__ {TYPE_1__ bit; } ;
struct TYPE_38__ {int freq_dfll; int* freq_gclk; int freq_xosc0; int* freq_dpll; } ;
struct TYPE_33__ {scalar_t__ GENCTRL0; } ;
struct TYPE_34__ {TYPE_18__ bit; } ;
struct TYPE_37__ {TYPE_19__ SYNCBUSY; TYPE_17__* GENCTRL; } ;
struct TYPE_36__ {TYPE_15__* Dpll; TYPE_4__ STATUS; TYPE_2__* XOSCCTRL; } ;
struct TYPE_31__ {int /*<<< orphan*/  SRC; } ;
struct TYPE_32__ {TYPE_16__ bit; } ;
struct TYPE_28__ {int LDR; } ;
struct TYPE_29__ {TYPE_13__ bit; } ;
struct TYPE_26__ {int REFCLK; int DIV; } ;
struct TYPE_27__ {TYPE_11__ bit; } ;
struct TYPE_25__ {TYPE_9__ bit; } ;
struct TYPE_30__ {TYPE_14__ DPLLRATIO; TYPE_12__ DPLLCTRLB; TYPE_10__ DPLLSTATUS; TYPE_8__ DPLLSYNCBUSY; TYPE_6__ DPLLCTRLA; } ;
typedef  TYPE_20__ Oscctrl ;
typedef  TYPE_21__ Gclk ;

/* Variables and functions */
 int /*<<< orphan*/  DBGC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_CLK_OSC_INIT_BEGIN ; 
 int /*<<< orphan*/  DC_CLK_OSC_INIT_COMPLETE ; 
 int /*<<< orphan*/  DC_CLK_OSC_INIT_DPLL_SYNC_DISABLE ; 
 int /*<<< orphan*/  DC_CLK_OSC_INIT_DPLL_SYNC_ENABLE ; 
 int /*<<< orphan*/  DC_CLK_OSC_INIT_DPLL_SYNC_RATIO ; 
 int /*<<< orphan*/  DC_CLK_OSC_INIT_DPLL_WAIT_CLKRDY ; 
 int /*<<< orphan*/  DC_CLK_OSC_INIT_DPLL_WAIT_LOCK ; 
 int /*<<< orphan*/  DC_CLK_OSC_INIT_GCLK_SYNC_GENCTRL0 ; 
 int /*<<< orphan*/  DC_CLK_OSC_INIT_XOSC0_SYNC ; 
 int FREQ_DFLL_DEFAULT ; 
 int FREQ_XOSC0 ; 
 TYPE_21__* GCLK ; 
 size_t GEN_DPLL0 ; 
 TYPE_20__* OSCCTRL ; 
 int PLL_RATIO ; 
 int USEC_DELAY_LOOP_CYCLES ; 
 int /*<<< orphan*/  USE_DPLL_DEF ; 
 size_t USE_DPLL_IND ; 
 TYPE_22__ system_clks ; 
 int usec_delay_mult ; 

void CLK_oscctrl_init(void) {
    Oscctrl *posctrl = OSCCTRL;
    Gclk *   pgclk   = GCLK;

    DBGC(DC_CLK_OSC_INIT_BEGIN);

    // default setup on por
    system_clks.freq_dfll    = FREQ_DFLL_DEFAULT;
    system_clks.freq_gclk[0] = system_clks.freq_dfll;

    // configure and startup 16MHz xosc0
    posctrl->XOSCCTRL[0].bit.ENABLE   = 0;
    posctrl->XOSCCTRL[0].bit.STARTUP  = 0xD;
    posctrl->XOSCCTRL[0].bit.ENALC    = 1;
    posctrl->XOSCCTRL[0].bit.IMULT    = 5;
    posctrl->XOSCCTRL[0].bit.IPTAT    = 3;
    posctrl->XOSCCTRL[0].bit.ONDEMAND = 0;
    posctrl->XOSCCTRL[0].bit.XTALEN   = 1;
    posctrl->XOSCCTRL[0].bit.ENABLE   = 1;
    while (posctrl->STATUS.bit.XOSCRDY0 == 0) {
        DBGC(DC_CLK_OSC_INIT_XOSC0_SYNC);
    }
    system_clks.freq_xosc0 = FREQ_XOSC0;

    // configure and startup DPLL
    posctrl->Dpll[USE_DPLL_IND].DPLLCTRLA.bit.ENABLE = 0;
    while (posctrl->Dpll[USE_DPLL_IND].DPLLSYNCBUSY.bit.ENABLE) {
        DBGC(DC_CLK_OSC_INIT_DPLL_SYNC_DISABLE);
    }
    posctrl->Dpll[USE_DPLL_IND].DPLLCTRLB.bit.REFCLK = 2;          // select XOSC0 (16MHz)
    posctrl->Dpll[USE_DPLL_IND].DPLLCTRLB.bit.DIV    = 7;          // 16 MHz / (2 * (7 + 1)) = 1 MHz
    posctrl->Dpll[USE_DPLL_IND].DPLLRATIO.bit.LDR    = PLL_RATIO;  // 1 MHz * (PLL_RATIO(47) + 1) = 48MHz
    while (posctrl->Dpll[USE_DPLL_IND].DPLLSYNCBUSY.bit.DPLLRATIO) {
        DBGC(DC_CLK_OSC_INIT_DPLL_SYNC_RATIO);
    }
    posctrl->Dpll[USE_DPLL_IND].DPLLCTRLA.bit.ONDEMAND = 0;
    posctrl->Dpll[USE_DPLL_IND].DPLLCTRLA.bit.ENABLE   = 1;
    while (posctrl->Dpll[USE_DPLL_IND].DPLLSYNCBUSY.bit.ENABLE) {
        DBGC(DC_CLK_OSC_INIT_DPLL_SYNC_ENABLE);
    }
    while (posctrl->Dpll[USE_DPLL_IND].DPLLSTATUS.bit.LOCK == 0) {
        DBGC(DC_CLK_OSC_INIT_DPLL_WAIT_LOCK);
    }
    while (posctrl->Dpll[USE_DPLL_IND].DPLLSTATUS.bit.CLKRDY == 0) {
        DBGC(DC_CLK_OSC_INIT_DPLL_WAIT_CLKRDY);
    }
    system_clks.freq_dpll[0] = (system_clks.freq_xosc0 / 2 / (posctrl->Dpll[USE_DPLL_IND].DPLLCTRLB.bit.DIV + 1)) * (posctrl->Dpll[USE_DPLL_IND].DPLLRATIO.bit.LDR + 1);

    // change gclk0 to DPLL
    pgclk->GENCTRL[GEN_DPLL0].bit.SRC = USE_DPLL_DEF;
    while (pgclk->SYNCBUSY.bit.GENCTRL0) {
        DBGC(DC_CLK_OSC_INIT_GCLK_SYNC_GENCTRL0);
    }

    system_clks.freq_gclk[0] = system_clks.freq_dpll[0];

    usec_delay_mult = system_clks.freq_gclk[0] / (USEC_DELAY_LOOP_CYCLES * 1000000);
    if (usec_delay_mult < 1) usec_delay_mult = 1;  // Never allow a multiplier of zero

    DBGC(DC_CLK_OSC_INIT_COMPLETE);
}