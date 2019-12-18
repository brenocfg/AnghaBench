#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_77__   TYPE_9__ ;
typedef  struct TYPE_76__   TYPE_8__ ;
typedef  struct TYPE_75__   TYPE_7__ ;
typedef  struct TYPE_74__   TYPE_6__ ;
typedef  struct TYPE_73__   TYPE_5__ ;
typedef  struct TYPE_72__   TYPE_4__ ;
typedef  struct TYPE_71__   TYPE_3__ ;
typedef  struct TYPE_70__   TYPE_36__ ;
typedef  struct TYPE_69__   TYPE_35__ ;
typedef  struct TYPE_68__   TYPE_34__ ;
typedef  struct TYPE_67__   TYPE_33__ ;
typedef  struct TYPE_66__   TYPE_32__ ;
typedef  struct TYPE_65__   TYPE_31__ ;
typedef  struct TYPE_64__   TYPE_30__ ;
typedef  struct TYPE_63__   TYPE_2__ ;
typedef  struct TYPE_62__   TYPE_29__ ;
typedef  struct TYPE_61__   TYPE_28__ ;
typedef  struct TYPE_60__   TYPE_27__ ;
typedef  struct TYPE_59__   TYPE_26__ ;
typedef  struct TYPE_58__   TYPE_25__ ;
typedef  struct TYPE_57__   TYPE_24__ ;
typedef  struct TYPE_56__   TYPE_23__ ;
typedef  struct TYPE_55__   TYPE_22__ ;
typedef  struct TYPE_54__   TYPE_21__ ;
typedef  struct TYPE_53__   TYPE_20__ ;
typedef  struct TYPE_52__   TYPE_1__ ;
typedef  struct TYPE_51__   TYPE_19__ ;
typedef  struct TYPE_50__   TYPE_18__ ;
typedef  struct TYPE_49__   TYPE_17__ ;
typedef  struct TYPE_48__   TYPE_16__ ;
typedef  struct TYPE_47__   TYPE_15__ ;
typedef  struct TYPE_46__   TYPE_14__ ;
typedef  struct TYPE_45__   TYPE_13__ ;
typedef  struct TYPE_44__   TYPE_12__ ;
typedef  struct TYPE_43__   TYPE_11__ ;
typedef  struct TYPE_42__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_55__ {int TCEI; int EVACT; } ;
struct TYPE_56__ {TYPE_22__ bit; } ;
struct TYPE_53__ {int SWRST; int MODE; scalar_t__ ENABLE; } ;
struct TYPE_54__ {TYPE_20__ bit; } ;
struct TYPE_50__ {scalar_t__ SWRST; scalar_t__ ENABLE; } ;
struct TYPE_51__ {TYPE_18__ bit; } ;
struct TYPE_57__ {TYPE_23__ EVCTRL; TYPE_21__ CTRLA; TYPE_19__ SYNCBUSY; } ;
struct TYPE_45__ {int MC0; } ;
struct TYPE_46__ {TYPE_13__ bit; } ;
struct TYPE_43__ {int MCEO0; } ;
struct TYPE_44__ {TYPE_11__ bit; } ;
struct TYPE_77__ {int WAVEGEN; } ;
struct TYPE_42__ {TYPE_9__ bit; } ;
struct TYPE_75__ {scalar_t__ CC0; scalar_t__ CTRLB; scalar_t__ SWRST; scalar_t__ ENABLE; } ;
struct TYPE_76__ {TYPE_7__ bit; } ;
struct TYPE_73__ {int reg; } ;
struct TYPE_71__ {int SWRST; scalar_t__ ENABLE; } ;
struct TYPE_72__ {TYPE_3__ bit; } ;
struct TYPE_47__ {TYPE_14__ INTENSET; TYPE_12__ EVCTRL; TYPE_10__ WAVE; TYPE_8__ SYNCBUSY; TYPE_6__* CC; TYPE_5__ CTRLBCLR; TYPE_4__ CTRLA; } ;
struct TYPE_67__ {TYPE_24__ COUNT32; TYPE_15__ COUNT16; } ;
typedef  TYPE_33__ Tc ;
struct TYPE_74__ {int reg; } ;
struct TYPE_70__ {TYPE_32__* Channel; TYPE_29__* USER; } ;
struct TYPE_69__ {TYPE_28__* PCHCTRL; } ;
struct TYPE_58__ {int EVSYS_; } ;
struct TYPE_59__ {TYPE_25__ bit; } ;
struct TYPE_48__ {int TC0_; int TC1_; } ;
struct TYPE_49__ {TYPE_16__ bit; } ;
struct TYPE_52__ {int TC4_; } ;
struct TYPE_63__ {TYPE_1__ bit; } ;
struct TYPE_68__ {TYPE_26__ APBBMASK; TYPE_17__ APBAMASK; TYPE_2__ APBCMASK; } ;
struct TYPE_64__ {int /*<<< orphan*/  EVGEN; int /*<<< orphan*/  PATH; int /*<<< orphan*/  EDGSEL; } ;
struct TYPE_65__ {TYPE_30__ bit; } ;
struct TYPE_66__ {TYPE_31__ CHANNEL; } ;
struct TYPE_62__ {int /*<<< orphan*/  reg; } ;
struct TYPE_60__ {int CHEN; void* GEN; } ;
struct TYPE_61__ {TYPE_27__ bit; } ;
typedef  TYPE_34__ Mclk ;
typedef  TYPE_35__ Gclk ;
typedef  TYPE_36__ Evsys ;

/* Variables and functions */
 int /*<<< orphan*/  ADC0_clock_init () ; 
 int /*<<< orphan*/  CLK_init_osc () ; 
 int /*<<< orphan*/  CLK_reset_time () ; 
 int /*<<< orphan*/  CLK_set_gclk_freq (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBGC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_CLK_ENABLE_TIMEBASE_BEGIN ; 
 int /*<<< orphan*/  DC_CLK_ENABLE_TIMEBASE_COMPLETE ; 
 int /*<<< orphan*/  DC_CLK_ENABLE_TIMEBASE_EVSYS_BEGIN ; 
 int /*<<< orphan*/  DC_CLK_ENABLE_TIMEBASE_EVSYS_COMPLETE ; 
 int /*<<< orphan*/  DC_CLK_ENABLE_TIMEBASE_TC0_BEGIN ; 
 int /*<<< orphan*/  DC_CLK_ENABLE_TIMEBASE_TC0_COMPLETE ; 
 int /*<<< orphan*/  DC_CLK_ENABLE_TIMEBASE_TC0_SYNC_DISABLE ; 
 int /*<<< orphan*/  DC_CLK_ENABLE_TIMEBASE_TC0_SYNC_SWRST_1 ; 
 int /*<<< orphan*/  DC_CLK_ENABLE_TIMEBASE_TC0_SYNC_SWRST_2 ; 
 int /*<<< orphan*/  DC_CLK_ENABLE_TIMEBASE_TC4_BEGIN ; 
 int /*<<< orphan*/  DC_CLK_ENABLE_TIMEBASE_TC4_COMPLETE ; 
 int /*<<< orphan*/  DC_CLK_ENABLE_TIMEBASE_TC4_SYNC_CC0 ; 
 int /*<<< orphan*/  DC_CLK_ENABLE_TIMEBASE_TC4_SYNC_CLTRB ; 
 int /*<<< orphan*/  DC_CLK_ENABLE_TIMEBASE_TC4_SYNC_DISABLE ; 
 int /*<<< orphan*/  DC_CLK_ENABLE_TIMEBASE_TC4_SYNC_SWRST_1 ; 
 int /*<<< orphan*/  DC_CLK_ENABLE_TIMEBASE_TC4_SYNC_SWRST_2 ; 
 TYPE_36__* EVSYS ; 
 int /*<<< orphan*/  EVSYS_CHANNEL_EDGSEL_RISING_EDGE_Val ; 
 int /*<<< orphan*/  EVSYS_CHANNEL_PATH_SYNCHRONOUS_Val ; 
 size_t EVSYS_GCLK_ID_0 ; 
 int /*<<< orphan*/  EVSYS_ID_GEN_TC4_MCX_0 ; 
 int /*<<< orphan*/  EVSYS_ID_USER_PORT_EV_0 ; 
 int /*<<< orphan*/  FREQ_TC45_DEFAULT ; 
 TYPE_35__* GCLK ; 
 void* GEN_TC45 ; 
 TYPE_34__* MCLK ; 
 int /*<<< orphan*/  NVIC_EnableIRQ (int /*<<< orphan*/ ) ; 
 TYPE_33__* TC0 ; 
 size_t TC0_GCLK_ID ; 
 size_t TC1_GCLK_ID ; 
 TYPE_33__* TC4 ; 
 size_t TC4_GCLK_ID ; 
 int /*<<< orphan*/  TC4_IRQn ; 

uint32_t CLK_enable_timebase(void) {
    Gclk * pgclk  = GCLK;
    Mclk * pmclk  = MCLK;
    Tc *   ptc4   = TC4;
    Tc *   ptc0   = TC0;
    Evsys *pevsys = EVSYS;

    DBGC(DC_CLK_ENABLE_TIMEBASE_BEGIN);

    // gclk2  highspeed time base
    CLK_set_gclk_freq(GEN_TC45, FREQ_TC45_DEFAULT);
    CLK_init_osc();

    // unmask TC4, sourcegclk2 to TC4
    pmclk->APBCMASK.bit.TC4_             = 1;
    pgclk->PCHCTRL[TC4_GCLK_ID].bit.GEN  = GEN_TC45;
    pgclk->PCHCTRL[TC4_GCLK_ID].bit.CHEN = 1;

    // configure TC4
    DBGC(DC_CLK_ENABLE_TIMEBASE_TC4_BEGIN);
    ptc4->COUNT16.CTRLA.bit.ENABLE = 0;
    while (ptc4->COUNT16.SYNCBUSY.bit.ENABLE) {
        DBGC(DC_CLK_ENABLE_TIMEBASE_TC4_SYNC_DISABLE);
    }
    ptc4->COUNT16.CTRLA.bit.SWRST = 1;
    while (ptc4->COUNT16.SYNCBUSY.bit.SWRST) {
        DBGC(DC_CLK_ENABLE_TIMEBASE_TC4_SYNC_SWRST_1);
    }
    while (ptc4->COUNT16.CTRLA.bit.SWRST) {
        DBGC(DC_CLK_ENABLE_TIMEBASE_TC4_SYNC_SWRST_2);
    }

    // CTRLA defaults
    // CTRLB as default, counting up
    ptc4->COUNT16.CTRLBCLR.reg = 5;
    while (ptc4->COUNT16.SYNCBUSY.bit.CTRLB) {
        DBGC(DC_CLK_ENABLE_TIMEBASE_TC4_SYNC_CLTRB);
    }
    ptc4->COUNT16.CC[0].reg = 999;
    while (ptc4->COUNT16.SYNCBUSY.bit.CC0) {
        DBGC(DC_CLK_ENABLE_TIMEBASE_TC4_SYNC_CC0);
    }
    // ptc4->COUNT16.DBGCTRL.bit.DBGRUN = 1;

    // wave mode
    ptc4->COUNT16.WAVE.bit.WAVEGEN = 1;  // MFRQ match frequency mode, toggle each CC match
    // generate event for next stage
    ptc4->COUNT16.EVCTRL.bit.MCEO0 = 1;

    NVIC_EnableIRQ(TC4_IRQn);
    ptc4->COUNT16.INTENSET.bit.MC0 = 1;

    DBGC(DC_CLK_ENABLE_TIMEBASE_TC4_COMPLETE);

    // unmask TC0,1, sourcegclk2 to TC0,1
    pmclk->APBAMASK.bit.TC0_             = 1;
    pgclk->PCHCTRL[TC0_GCLK_ID].bit.GEN  = GEN_TC45;
    pgclk->PCHCTRL[TC0_GCLK_ID].bit.CHEN = 1;

    pmclk->APBAMASK.bit.TC1_             = 1;
    pgclk->PCHCTRL[TC1_GCLK_ID].bit.GEN  = GEN_TC45;
    pgclk->PCHCTRL[TC1_GCLK_ID].bit.CHEN = 1;

    // configure TC0
    DBGC(DC_CLK_ENABLE_TIMEBASE_TC0_BEGIN);
    ptc0->COUNT32.CTRLA.bit.ENABLE = 0;
    while (ptc0->COUNT32.SYNCBUSY.bit.ENABLE) {
        DBGC(DC_CLK_ENABLE_TIMEBASE_TC0_SYNC_DISABLE);
    }
    ptc0->COUNT32.CTRLA.bit.SWRST = 1;
    while (ptc0->COUNT32.SYNCBUSY.bit.SWRST) {
        DBGC(DC_CLK_ENABLE_TIMEBASE_TC0_SYNC_SWRST_1);
    }
    while (ptc0->COUNT32.CTRLA.bit.SWRST) {
        DBGC(DC_CLK_ENABLE_TIMEBASE_TC0_SYNC_SWRST_2);
    }
    // CTRLA as default
    ptc0->COUNT32.CTRLA.bit.MODE   = 2;  // 32 bit mode
    ptc0->COUNT32.EVCTRL.bit.TCEI  = 1;  // enable incoming events
    ptc0->COUNT32.EVCTRL.bit.EVACT = 2;  // count events

    DBGC(DC_CLK_ENABLE_TIMEBASE_TC0_COMPLETE);

    DBGC(DC_CLK_ENABLE_TIMEBASE_EVSYS_BEGIN);

    // configure event system
    pmclk->APBBMASK.bit.EVSYS_               = 1;
    pgclk->PCHCTRL[EVSYS_GCLK_ID_0].bit.GEN  = GEN_TC45;
    pgclk->PCHCTRL[EVSYS_GCLK_ID_0].bit.CHEN = 1;
    pevsys->USER[44].reg                     = EVSYS_ID_USER_PORT_EV_0;               // TC0 will get event channel 0
    pevsys->Channel[0].CHANNEL.bit.EDGSEL    = EVSYS_CHANNEL_EDGSEL_RISING_EDGE_Val;  // Rising edge
    pevsys->Channel[0].CHANNEL.bit.PATH      = EVSYS_CHANNEL_PATH_SYNCHRONOUS_Val;    // Synchronous
    pevsys->Channel[0].CHANNEL.bit.EVGEN     = EVSYS_ID_GEN_TC4_MCX_0;                // TC4 MC0

    DBGC(DC_CLK_ENABLE_TIMEBASE_EVSYS_COMPLETE);

    CLK_reset_time();

    ADC0_clock_init();

    DBGC(DC_CLK_ENABLE_TIMEBASE_COMPLETE);

    return 0;
}