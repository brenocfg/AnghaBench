#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_9__ ;
typedef  struct TYPE_39__   TYPE_8__ ;
typedef  struct TYPE_38__   TYPE_7__ ;
typedef  struct TYPE_37__   TYPE_6__ ;
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_20__ ;
typedef  struct TYPE_31__   TYPE_1__ ;
typedef  struct TYPE_30__   TYPE_19__ ;
typedef  struct TYPE_29__   TYPE_18__ ;
typedef  struct TYPE_28__   TYPE_17__ ;
typedef  struct TYPE_27__   TYPE_16__ ;
typedef  struct TYPE_26__   TYPE_15__ ;
typedef  struct TYPE_25__   TYPE_14__ ;
typedef  struct TYPE_24__   TYPE_13__ ;
typedef  struct TYPE_23__   TYPE_12__ ;
typedef  struct TYPE_22__   TYPE_11__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_40__ {scalar_t__ SYNCBUSY; } ;
struct TYPE_39__ {int reg; } ;
struct TYPE_37__ {int /*<<< orphan*/  DFLLRDY; } ;
struct TYPE_38__ {TYPE_6__ bit; } ;
struct TYPE_36__ {void* reg; } ;
struct TYPE_35__ {int reg; } ;
struct TYPE_34__ {int reg; } ;
struct TYPE_31__ {int MANW; int RWS; } ;
struct TYPE_33__ {TYPE_1__ bit; } ;
struct TYPE_24__ {scalar_t__ GENCTRL1; } ;
struct TYPE_25__ {TYPE_13__ bit; } ;
struct TYPE_21__ {TYPE_9__ bit; } ;
struct TYPE_32__ {TYPE_14__ SYNCBUSY; TYPE_12__* GENCTRL; TYPE_10__ STATUS; TYPE_8__ GENDIV; } ;
struct TYPE_30__ {TYPE_2__ CTRLB; } ;
struct TYPE_29__ {TYPE_16__* Group; } ;
struct TYPE_28__ {TYPE_7__ PCLKSR; TYPE_5__ DFLLCTRL; TYPE_4__ DFLLVAL; TYPE_3__ DFLLMUL; } ;
struct TYPE_26__ {int reg; } ;
struct TYPE_27__ {TYPE_15__ DIRSET; } ;
struct TYPE_23__ {int reg; } ;
struct TYPE_22__ {int reg; } ;

/* Variables and functions */
 int CPU_FREQ ; 
 scalar_t__ FUSES_DFLL48M_COARSE_CAL_ADDR ; 
 int FUSES_DFLL48M_COARSE_CAL_Msk ; 
 int FUSES_DFLL48M_COARSE_CAL_Pos ; 
 TYPE_20__* GCLK ; 
 int GCLK_GENCTRL_DIV_Pos ; 
 int GCLK_GENCTRL_GENEN ; 
 int GCLK_GENCTRL_ID (int /*<<< orphan*/ ) ; 
 int GCLK_GENCTRL_SRC_DFLL ; 
 int GCLK_GENCTRL_SRC_DFLL48M ; 
 int GCLK_GENDIV_DIV (int) ; 
 int GCLK_GENDIV_ID (int /*<<< orphan*/ ) ; 
 TYPE_19__* NVMCTRL ; 
 TYPE_18__* PORT ; 
 TYPE_17__* SYSCTRL ; 
 void* SYSCTRL_DFLLCTRL_CCDIS ; 
 void* SYSCTRL_DFLLCTRL_ENABLE ; 
 void* SYSCTRL_DFLLCTRL_MODE ; 
 void* SYSCTRL_DFLLCTRL_USBCRM ; 
 int SYSCTRL_DFLLMUL_CSTEP (int) ; 
 int SYSCTRL_DFLLMUL_FSTEP (int) ; 
 int SYSCTRL_DFLLMUL_MUL (int) ; 
 int SYSCTRL_DFLLVAL_COARSE (int) ; 
 int SYSCTRL_DFLLVAL_FINE (int) ; 
 int /*<<< orphan*/  SysTick_Config (int) ; 
 int /*<<< orphan*/  uart0_init () ; 
 int /*<<< orphan*/  usb_init () ; 

void samd_init(void) {
    #if defined(MCU_SAMD21)

    NVMCTRL->CTRLB.bit.MANW = 1; // errata "Spurious Writes"
    NVMCTRL->CTRLB.bit.RWS = 1; // 1 read wait state for 48MHz

    // Enable DFLL48M
    SYSCTRL->DFLLCTRL.reg = SYSCTRL_DFLLCTRL_ENABLE;
    while (!SYSCTRL->PCLKSR.bit.DFLLRDY) {}
    SYSCTRL->DFLLMUL.reg = SYSCTRL_DFLLMUL_CSTEP(1) | SYSCTRL_DFLLMUL_FSTEP(1)
        | SYSCTRL_DFLLMUL_MUL(48000);
    uint32_t coarse = (*((uint32_t*)FUSES_DFLL48M_COARSE_CAL_ADDR) & FUSES_DFLL48M_COARSE_CAL_Msk)
        >> FUSES_DFLL48M_COARSE_CAL_Pos;
    if (coarse == 0x3f) {
        coarse = 0x1f;
    }
    uint32_t fine = 512;
    SYSCTRL->DFLLVAL.reg = SYSCTRL_DFLLVAL_COARSE(coarse) | SYSCTRL_DFLLVAL_FINE(fine);
    SYSCTRL->DFLLCTRL.reg = SYSCTRL_DFLLCTRL_CCDIS | SYSCTRL_DFLLCTRL_USBCRM
        | SYSCTRL_DFLLCTRL_MODE | SYSCTRL_DFLLCTRL_ENABLE;
    while (!SYSCTRL->PCLKSR.bit.DFLLRDY) {}

    GCLK->GENDIV.reg = GCLK_GENDIV_ID(0) | GCLK_GENDIV_DIV(1);
    GCLK->GENCTRL.reg = GCLK_GENCTRL_GENEN | GCLK_GENCTRL_SRC_DFLL48M | GCLK_GENCTRL_ID(0);
    while (GCLK->STATUS.bit.SYNCBUSY) { }

    // Configure PA10 as output for LED
    PORT->Group[0].DIRSET.reg = 1 << 10;

    #elif defined(MCU_SAMD51)

    GCLK->GENCTRL[1].reg = 1 << GCLK_GENCTRL_DIV_Pos | GCLK_GENCTRL_GENEN | GCLK_GENCTRL_SRC_DFLL;
    while (GCLK->SYNCBUSY.bit.GENCTRL1) { }

    // Configure PA22 as output for LED
    PORT->Group[0].DIRSET.reg = 1 << 22;

    #endif

    SysTick_Config(CPU_FREQ / 1000);
    uart0_init();
    usb_init();
}