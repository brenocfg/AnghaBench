#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_13__ {int /*<<< orphan*/  freq_xosc0; int /*<<< orphan*/ * freq_gclk; } ;
struct TYPE_10__ {scalar_t__ GENCTRL; } ;
struct TYPE_11__ {TYPE_3__ vec; } ;
struct TYPE_12__ {TYPE_4__ SYNCBUSY; TYPE_2__* GENCTRL; } ;
struct TYPE_8__ {int DIV; int GENEN; scalar_t__ DIVSEL; int /*<<< orphan*/  SRC; } ;
struct TYPE_9__ {TYPE_1__ bit; } ;
typedef  TYPE_5__ Gclk ;

/* Variables and functions */
 int /*<<< orphan*/  DBGC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_CLK_INIT_OSC_BEGIN ; 
 int /*<<< orphan*/  DC_CLK_INIT_OSC_COMPLETE ; 
 int /*<<< orphan*/  DC_CLK_INIT_OSC_SYNC_1 ; 
 int /*<<< orphan*/  DC_CLK_INIT_OSC_SYNC_2 ; 
 int /*<<< orphan*/  DC_CLK_INIT_OSC_SYNC_3 ; 
 int /*<<< orphan*/  DC_CLK_INIT_OSC_SYNC_4 ; 
 int /*<<< orphan*/  DC_CLK_INIT_OSC_SYNC_5 ; 
 TYPE_5__* GCLK ; 
 int /*<<< orphan*/  GCLK_SOURCE_XOSC0 ; 
 size_t GEN_OSC0 ; 
 TYPE_6__ system_clks ; 

void CLK_init_osc(void) {
    uint8_t gclkn = GEN_OSC0;
    Gclk *  pgclk = GCLK;

    DBGC(DC_CLK_INIT_OSC_BEGIN);

    while (pgclk->SYNCBUSY.vec.GENCTRL) {
        DBGC(DC_CLK_INIT_OSC_SYNC_1);
    }
    pgclk->GENCTRL[gclkn].bit.SRC = GCLK_SOURCE_XOSC0;
    while (pgclk->SYNCBUSY.vec.GENCTRL) {
        DBGC(DC_CLK_INIT_OSC_SYNC_2);
    }
    pgclk->GENCTRL[gclkn].bit.DIV = 1;
    while (pgclk->SYNCBUSY.vec.GENCTRL) {
        DBGC(DC_CLK_INIT_OSC_SYNC_3);
    }
    pgclk->GENCTRL[gclkn].bit.DIVSEL = 0;
    while (pgclk->SYNCBUSY.vec.GENCTRL) {
        DBGC(DC_CLK_INIT_OSC_SYNC_4);
    }
    pgclk->GENCTRL[gclkn].bit.GENEN = 1;
    while (pgclk->SYNCBUSY.vec.GENCTRL) {
        DBGC(DC_CLK_INIT_OSC_SYNC_5);
    }
    system_clks.freq_gclk[gclkn] = system_clks.freq_xosc0;

    DBGC(DC_CLK_INIT_OSC_COMPLETE);
}