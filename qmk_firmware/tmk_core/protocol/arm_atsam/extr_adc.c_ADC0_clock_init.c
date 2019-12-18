#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_4__* PCHCTRL; } ;
struct TYPE_7__ {int ADC0_; } ;
struct TYPE_8__ {TYPE_1__ bit; } ;
struct TYPE_11__ {TYPE_2__ APBDMASK; } ;
struct TYPE_9__ {int CHEN; int /*<<< orphan*/  GEN; } ;
struct TYPE_10__ {TYPE_3__ bit; } ;

/* Variables and functions */
 size_t ADC0_GCLK_ID ; 
 int /*<<< orphan*/  DBGC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_ADC0_CLOCK_INIT_BEGIN ; 
 int /*<<< orphan*/  DC_ADC0_CLOCK_INIT_COMPLETE ; 
 TYPE_6__* GCLK ; 
 int /*<<< orphan*/  GEN_OSC0 ; 
 TYPE_5__* MCLK ; 

void ADC0_clock_init(void) {
    DBGC(DC_ADC0_CLOCK_INIT_BEGIN);

    MCLK->APBDMASK.bit.ADC0_ = 1;  // ADC0 Clock Enable

    GCLK->PCHCTRL[ADC0_GCLK_ID].bit.GEN  = GEN_OSC0;  // Select generator clock
    GCLK->PCHCTRL[ADC0_GCLK_ID].bit.CHEN = 1;         // Enable peripheral clock

    DBGC(DC_ADC0_CLOCK_INIT_COMPLETE);
}