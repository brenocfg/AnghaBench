#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_79__   TYPE_9__ ;
typedef  struct TYPE_78__   TYPE_8__ ;
typedef  struct TYPE_77__   TYPE_7__ ;
typedef  struct TYPE_76__   TYPE_6__ ;
typedef  struct TYPE_75__   TYPE_5__ ;
typedef  struct TYPE_74__   TYPE_4__ ;
typedef  struct TYPE_73__   TYPE_3__ ;
typedef  struct TYPE_72__   TYPE_37__ ;
typedef  struct TYPE_71__   TYPE_36__ ;
typedef  struct TYPE_70__   TYPE_35__ ;
typedef  struct TYPE_69__   TYPE_34__ ;
typedef  struct TYPE_68__   TYPE_33__ ;
typedef  struct TYPE_67__   TYPE_32__ ;
typedef  struct TYPE_66__   TYPE_31__ ;
typedef  struct TYPE_65__   TYPE_30__ ;
typedef  struct TYPE_64__   TYPE_2__ ;
typedef  struct TYPE_63__   TYPE_29__ ;
typedef  struct TYPE_62__   TYPE_28__ ;
typedef  struct TYPE_61__   TYPE_27__ ;
typedef  struct TYPE_60__   TYPE_26__ ;
typedef  struct TYPE_59__   TYPE_25__ ;
typedef  struct TYPE_58__   TYPE_24__ ;
typedef  struct TYPE_57__   TYPE_23__ ;
typedef  struct TYPE_56__   TYPE_22__ ;
typedef  struct TYPE_55__   TYPE_21__ ;
typedef  struct TYPE_54__   TYPE_20__ ;
typedef  struct TYPE_53__   TYPE_1__ ;
typedef  struct TYPE_52__   TYPE_19__ ;
typedef  struct TYPE_51__   TYPE_18__ ;
typedef  struct TYPE_50__   TYPE_17__ ;
typedef  struct TYPE_49__   TYPE_16__ ;
typedef  struct TYPE_48__   TYPE_15__ ;
typedef  struct TYPE_47__   TYPE_14__ ;
typedef  struct TYPE_46__   TYPE_13__ ;
typedef  struct TYPE_45__   TYPE_12__ ;
typedef  struct TYPE_44__   TYPE_11__ ;
typedef  struct TYPE_43__   TYPE_10__ ;

/* Type definitions */
struct TYPE_59__ {int DQOS; int CQOS; } ;
struct TYPE_60__ {TYPE_25__ bit; } ;
struct TYPE_57__ {scalar_t__ ENABLE; scalar_t__ SWRST; } ;
struct TYPE_58__ {TYPE_23__ bit; } ;
struct TYPE_55__ {int SWRST; int ENABLE; scalar_t__ MODE; } ;
struct TYPE_56__ {TYPE_21__ bit; } ;
struct TYPE_52__ {scalar_t__ SPDCONF; } ;
struct TYPE_54__ {TYPE_19__ bit; } ;
struct TYPE_50__ {int TRANSN; int TRANSP; int TRIM; } ;
struct TYPE_51__ {TYPE_17__ bit; } ;
struct TYPE_61__ {TYPE_26__ QOSCTRL; TYPE_24__ SYNCBUSY; TYPE_22__ CTRLA; TYPE_20__ CTRLB; TYPE_18__ PADCAL; } ;
struct TYPE_67__ {TYPE_27__ DEVICE; } ;
typedef  TYPE_32__ Usb ;
struct TYPE_79__ {int USBCRM; int MODE; int CCDIS; scalar_t__ QLDIS; } ;
struct TYPE_77__ {int PMUXE; } ;
struct TYPE_78__ {int reg; TYPE_7__ bit; } ;
struct TYPE_75__ {int USB_; } ;
struct TYPE_76__ {TYPE_5__ bit; } ;
struct TYPE_73__ {int USB_; } ;
struct TYPE_74__ {TYPE_3__ bit; } ;
struct TYPE_66__ {int HUB_CONNECT; int HUB_RESET_N; } ;
struct TYPE_72__ {TYPE_31__ bit; } ;
struct TYPE_71__ {TYPE_2__* PCHCTRL; } ;
struct TYPE_70__ {TYPE_6__ APBBMASK; TYPE_4__ AHBMASK; } ;
struct TYPE_48__ {scalar_t__ ENABLE; scalar_t__ DFLLMUL; scalar_t__ DFLLCTRLB; } ;
struct TYPE_49__ {TYPE_15__ bit; } ;
struct TYPE_46__ {int ENABLE; } ;
struct TYPE_47__ {TYPE_13__ bit; } ;
struct TYPE_44__ {int MUL; } ;
struct TYPE_45__ {TYPE_11__ bit; } ;
struct TYPE_43__ {TYPE_9__ bit; } ;
struct TYPE_69__ {TYPE_16__ DFLLSYNC; TYPE_14__ DFLLCTRLA; TYPE_12__ DFLLMUL; TYPE_10__ DFLLCTRLB; } ;
struct TYPE_68__ {TYPE_30__* Group; } ;
struct TYPE_65__ {TYPE_29__* PINCFG; TYPE_8__* PMUX; } ;
struct TYPE_53__ {int CHEN; scalar_t__ GEN; } ;
struct TYPE_64__ {TYPE_1__ bit; } ;
struct TYPE_62__ {int PMUXEN; int INEN; } ;
struct TYPE_63__ {TYPE_28__ bit; } ;
typedef  TYPE_33__ Port ;
typedef  TYPE_34__ Oscctrl ;
typedef  TYPE_35__ Mclk ;
typedef  TYPE_36__ Gclk ;

/* Variables and functions */
 int /*<<< orphan*/  ADC_5V ; 
 int /*<<< orphan*/  ADC_5V_START_LEVEL ; 
 int /*<<< orphan*/  DBGC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_USB2422_INIT_BEGIN ; 
 int /*<<< orphan*/  DC_USB2422_INIT_COMPLETE ; 
 int /*<<< orphan*/  DC_USB2422_INIT_OSC_SYNC_DFLLCTRLB_1 ; 
 int /*<<< orphan*/  DC_USB2422_INIT_OSC_SYNC_DFLLCTRLB_2 ; 
 int /*<<< orphan*/  DC_USB2422_INIT_OSC_SYNC_DFLLCTRLB_3 ; 
 int /*<<< orphan*/  DC_USB2422_INIT_OSC_SYNC_DFLLCTRLB_4 ; 
 int /*<<< orphan*/  DC_USB2422_INIT_OSC_SYNC_DFLLMUL ; 
 int /*<<< orphan*/  DC_USB2422_INIT_OSC_SYNC_DISABLING ; 
 int /*<<< orphan*/  DC_USB2422_INIT_OSC_SYNC_ENABLING ; 
 int /*<<< orphan*/  DC_USB2422_INIT_USB_SYNC_ENABLING ; 
 int /*<<< orphan*/  DC_USB2422_INIT_USB_SYNC_SWRST ; 
 int /*<<< orphan*/  DC_USB2422_INIT_USB_WAIT_SWRST ; 
 int /*<<< orphan*/  DC_USB2422_INIT_WAIT_5V_LOW ; 
 TYPE_36__* GCLK ; 
 TYPE_35__* MCLK ; 
 TYPE_34__* OSCCTRL ; 
 TYPE_33__* PORT ; 
 int /*<<< orphan*/  SR_EXP_WriteData () ; 
 TYPE_32__* USB ; 
 size_t USB2422_HUB_ACTIVE_GROUP ; 
 size_t USB2422_HUB_ACTIVE_PIN ; 
 int USB_FUSES_TRANSN_ADDR ; 
 int USB_FUSES_TRANSN_Msk ; 
 int USB_FUSES_TRANSN_Pos ; 
 int USB_FUSES_TRANSP_ADDR ; 
 int USB_FUSES_TRANSP_Msk ; 
 int USB_FUSES_TRANSP_Pos ; 
 int USB_FUSES_TRIM_ADDR ; 
 int USB_FUSES_TRIM_Msk ; 
 int USB_FUSES_TRIM_Pos ; 
 int /*<<< orphan*/  adc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c0_init () ; 
 TYPE_37__ sr_exp_data ; 
 scalar_t__ usb_extra_manual ; 
 int usb_gcr_auto ; 
 int /*<<< orphan*/  v_5v ; 
 int /*<<< orphan*/  wait_us (int) ; 

void USB2422_init(void) {
    Gclk *   pgclk = GCLK;
    Mclk *   pmclk = MCLK;
    Port *   pport = PORT;
    Oscctrl *posc  = OSCCTRL;
    Usb *    pusb  = USB;

    DBGC(DC_USB2422_INIT_BEGIN);

    while ((v_5v = adc_get(ADC_5V)) < ADC_5V_START_LEVEL) {
        DBGC(DC_USB2422_INIT_WAIT_5V_LOW);
    }

    // setup peripheral and synchronous bus clocks to USB
    pgclk->PCHCTRL[10].bit.GEN  = 0;
    pgclk->PCHCTRL[10].bit.CHEN = 1;
    pmclk->AHBMASK.bit.USB_     = 1;
    pmclk->APBBMASK.bit.USB_    = 1;

    // setup port pins for D-, D+, and SOF_1KHZ
    pport->Group[0].PMUX[12].reg          = 0x77;  // PA24, PA25, function column H for USB D-, D+
    pport->Group[0].PINCFG[24].bit.PMUXEN = 1;
    pport->Group[0].PINCFG[25].bit.PMUXEN = 1;
    pport->Group[1].PMUX[11].bit.PMUXE    = 7;  // PB22, function column H for USB SOF_1KHz output
    pport->Group[1].PINCFG[22].bit.PMUXEN = 1;

    // configure and enable DFLL for USB clock recovery mode at 48MHz
    posc->DFLLCTRLA.bit.ENABLE = 0;
    while (posc->DFLLSYNC.bit.ENABLE) {
        DBGC(DC_USB2422_INIT_OSC_SYNC_DISABLING);
    }
    while (posc->DFLLSYNC.bit.DFLLCTRLB) {
        DBGC(DC_USB2422_INIT_OSC_SYNC_DFLLCTRLB_1);
    }
    posc->DFLLCTRLB.bit.USBCRM = 1;
    while (posc->DFLLSYNC.bit.DFLLCTRLB) {
        DBGC(DC_USB2422_INIT_OSC_SYNC_DFLLCTRLB_2);
    }
    posc->DFLLCTRLB.bit.MODE = 1;
    while (posc->DFLLSYNC.bit.DFLLCTRLB) {
        DBGC(DC_USB2422_INIT_OSC_SYNC_DFLLCTRLB_3);
    }
    posc->DFLLCTRLB.bit.QLDIS = 0;
    while (posc->DFLLSYNC.bit.DFLLCTRLB) {
        DBGC(DC_USB2422_INIT_OSC_SYNC_DFLLCTRLB_4);
    }
    posc->DFLLCTRLB.bit.CCDIS = 1;
    posc->DFLLMUL.bit.MUL     = 0xBB80;  // 4800 x 1KHz
    while (posc->DFLLSYNC.bit.DFLLMUL) {
        DBGC(DC_USB2422_INIT_OSC_SYNC_DFLLMUL);
    }
    posc->DFLLCTRLA.bit.ENABLE = 1;
    while (posc->DFLLSYNC.bit.ENABLE) {
        DBGC(DC_USB2422_INIT_OSC_SYNC_ENABLING);
    }

    pusb->DEVICE.CTRLA.bit.SWRST = 1;
    while (pusb->DEVICE.SYNCBUSY.bit.SWRST) {
        DBGC(DC_USB2422_INIT_USB_SYNC_SWRST);
    }
    while (pusb->DEVICE.CTRLA.bit.SWRST) {
        DBGC(DC_USB2422_INIT_USB_WAIT_SWRST);
    }
    // calibration from factory presets
    pusb->DEVICE.PADCAL.bit.TRANSN = (USB_FUSES_TRANSN_ADDR >> USB_FUSES_TRANSN_Pos) & USB_FUSES_TRANSN_Msk;
    pusb->DEVICE.PADCAL.bit.TRANSP = (USB_FUSES_TRANSP_ADDR >> USB_FUSES_TRANSP_Pos) & USB_FUSES_TRANSP_Msk;
    pusb->DEVICE.PADCAL.bit.TRIM   = (USB_FUSES_TRIM_ADDR >> USB_FUSES_TRIM_Pos) & USB_FUSES_TRIM_Msk;
    // device mode, enabled
    pusb->DEVICE.CTRLB.bit.SPDCONF = 0;  // full speed
    pusb->DEVICE.CTRLA.bit.MODE    = 0;
    pusb->DEVICE.CTRLA.bit.ENABLE  = 1;
    while (pusb->DEVICE.SYNCBUSY.bit.ENABLE) {
        DBGC(DC_USB2422_INIT_USB_SYNC_ENABLING);
    }

    pusb->DEVICE.QOSCTRL.bit.DQOS = 2;
    pusb->DEVICE.QOSCTRL.bit.CQOS = 2;

    pport->Group[USB2422_HUB_ACTIVE_GROUP].PINCFG[USB2422_HUB_ACTIVE_PIN].bit.INEN = 1;

    i2c0_init();  // IC2 clk must be high at USB2422 reset release time to signal SMB configuration

    sr_exp_data.bit.HUB_CONNECT = 1;  // connect signal
    sr_exp_data.bit.HUB_RESET_N = 1;  // reset high
    SR_EXP_WriteData();

    wait_us(100);

#ifndef MD_BOOTLOADER

    usb_extra_manual = 0;
    usb_gcr_auto     = 1;

#endif  // MD_BOOTLOADER

    DBGC(DC_USB2422_INIT_COMPLETE);
}