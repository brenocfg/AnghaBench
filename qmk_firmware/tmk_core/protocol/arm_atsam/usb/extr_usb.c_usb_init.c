#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_80__   TYPE_9__ ;
typedef  struct TYPE_79__   TYPE_8__ ;
typedef  struct TYPE_78__   TYPE_7__ ;
typedef  struct TYPE_77__   TYPE_6__ ;
typedef  struct TYPE_76__   TYPE_5__ ;
typedef  struct TYPE_75__   TYPE_4__ ;
typedef  struct TYPE_74__   TYPE_3__ ;
typedef  struct TYPE_73__   TYPE_38__ ;
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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_64__ {int /*<<< orphan*/  SPDCONF; } ;
struct TYPE_74__ {TYPE_2__ bit; } ;
struct TYPE_53__ {int reg; } ;
struct TYPE_57__ {int SWRST; int /*<<< orphan*/  RUNSTDBY; int /*<<< orphan*/  MODE; } ;
struct TYPE_58__ {TYPE_23__ bit; } ;
struct TYPE_65__ {int TRANSN; int TRANSP; int TRIM; } ;
struct TYPE_66__ {TYPE_30__ bit; } ;
struct TYPE_59__ {scalar_t__ SWRST; } ;
struct TYPE_60__ {TYPE_25__ bit; } ;
struct TYPE_67__ {TYPE_3__ CTRLB; TYPE_1__ DESCADD; TYPE_24__ CTRLA; TYPE_31__ PADCAL; TYPE_26__ SYNCBUSY; } ;
struct usb_module {scalar_t__ speed_mode; scalar_t__* device_endpoint_enabled_callback_mask; scalar_t__* device_endpoint_registered_callback_mask; scalar_t__ device_enabled_callback_mask; scalar_t__ device_registered_callback_mask; int /*<<< orphan*/ *** device_endpoint_callback; int /*<<< orphan*/ ** device_callback; TYPE_32__ DEVICE; struct usb_module* hw; int /*<<< orphan*/  run_in_standby; int /*<<< orphan*/  select_host_mode; } ;
struct usb_config {scalar_t__ speed_mode; scalar_t__* device_endpoint_enabled_callback_mask; scalar_t__* device_endpoint_registered_callback_mask; scalar_t__ device_enabled_callback_mask; scalar_t__ device_registered_callback_mask; int /*<<< orphan*/ *** device_endpoint_callback; int /*<<< orphan*/ ** device_callback; TYPE_32__ DEVICE; struct usb_config* hw; int /*<<< orphan*/  run_in_standby; int /*<<< orphan*/  select_host_mode; } ;
typedef  enum status_code { ____Placeholder_status_code } status_code ;
typedef  struct usb_module Usb ;
struct TYPE_79__ {int PMUXE; } ;
struct TYPE_80__ {int reg; TYPE_8__ bit; } ;
struct TYPE_77__ {int USB_; } ;
struct TYPE_78__ {TYPE_6__ bit; } ;
struct TYPE_75__ {int USB_; } ;
struct TYPE_76__ {TYPE_4__ bit; } ;
struct TYPE_61__ {int CQOS; int DQOS; } ;
struct TYPE_62__ {TYPE_27__ bit; } ;
struct TYPE_63__ {TYPE_28__ QOSCTRL; } ;
struct TYPE_73__ {TYPE_29__ DEVICE; } ;
struct TYPE_72__ {int /*<<< orphan*/ * usb_endpoint_table; } ;
struct TYPE_71__ {TYPE_22__* PCHCTRL; } ;
struct TYPE_70__ {TYPE_7__ APBBMASK; TYPE_5__ AHBMASK; } ;
struct TYPE_52__ {scalar_t__ ENABLE; scalar_t__ DFLLMUL; scalar_t__ DFLLCTRLB; } ;
struct TYPE_54__ {TYPE_19__ bit; } ;
struct TYPE_50__ {int ENABLE; } ;
struct TYPE_51__ {TYPE_17__ bit; } ;
struct TYPE_48__ {int MUL; } ;
struct TYPE_49__ {TYPE_15__ bit; } ;
struct TYPE_46__ {int USBCRM; int MODE; int CCDIS; scalar_t__ QLDIS; } ;
struct TYPE_47__ {TYPE_13__ bit; } ;
struct TYPE_69__ {TYPE_20__ DFLLSYNC; TYPE_18__ DFLLCTRLA; TYPE_16__ DFLLMUL; TYPE_14__ DFLLCTRLB; } ;
struct TYPE_68__ {TYPE_12__* Group; } ;
struct TYPE_55__ {int CHEN; scalar_t__ GEN; } ;
struct TYPE_56__ {TYPE_21__ bit; } ;
struct TYPE_45__ {TYPE_11__* PINCFG; TYPE_9__* PMUX; } ;
struct TYPE_43__ {int PMUXEN; } ;
struct TYPE_44__ {TYPE_10__ bit; } ;
typedef  TYPE_33__ Port ;
typedef  TYPE_34__ Oscctrl ;
typedef  TYPE_35__ Mclk ;
typedef  TYPE_36__ Gclk ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (struct usb_module* const) ; 
 TYPE_36__* GCLK ; 
 size_t GCLK_USB ; 
 TYPE_35__* MCLK ; 
 int /*<<< orphan*/  NVIC_EnableIRQ (int /*<<< orphan*/ ) ; 
 TYPE_34__* OSCCTRL ; 
 TYPE_33__* PORT ; 
 int STATUS_OK ; 
 TYPE_38__* USB ; 
 int /*<<< orphan*/  USB_0_IRQn ; 
 int /*<<< orphan*/  USB_2_IRQn ; 
 int /*<<< orphan*/  USB_3_IRQn ; 
 int USB_DEVICE_CALLBACK_N ; 
 int /*<<< orphan*/  USB_DEVICE_CTRLB_SPDCONF_FS_Val ; 
 int /*<<< orphan*/  USB_DEVICE_CTRLB_SPDCONF_LS_Val ; 
 int USB_DEVICE_EP_CALLBACK_N ; 
 int USB_EPT_NUM ; 
 int USB_FUSES_TRANSN_ADDR ; 
 int USB_FUSES_TRANSN_Msk ; 
 int USB_FUSES_TRANSN_Pos ; 
 int USB_FUSES_TRANSP_ADDR ; 
 int USB_FUSES_TRANSP_Msk ; 
 int USB_FUSES_TRANSP_Pos ; 
 int USB_FUSES_TRIM_ADDR ; 
 int USB_FUSES_TRIM_Msk ; 
 int USB_FUSES_TRIM_Pos ; 
 scalar_t__ USB_SPEED_FULL ; 
 scalar_t__ USB_SPEED_LOW ; 
 struct usb_module* _usb_instances ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_37__ usb_descriptor_table ; 

enum status_code usb_init(struct usb_module *module_inst, Usb *const hw, struct usb_config *module_config) {
    /* Sanity check arguments */
    Assert(hw);
    Assert(module_inst);
    Assert(module_config);

    uint32_t i, j;
    uint32_t pad_transn, pad_transp, pad_trim;

    Gclk *   pgclk = GCLK;
    Mclk *   pmclk = MCLK;
    Port *   pport = PORT;
    Oscctrl *posc  = OSCCTRL;

    _usb_instances = module_inst;

    /* Associate the software module instance with the hardware module */
    module_inst->hw = hw;

    // setup peripheral and synchronous bus clocks to USB
    pmclk->AHBMASK.bit.USB_  = 1;
    pmclk->APBBMASK.bit.USB_ = 1;

    /* Set up the USB DP/DN pins */
    pport->Group[0].PMUX[12].reg          = 0x77;  // PA24, PA25, function column H for USB D-, D+
    pport->Group[0].PINCFG[24].bit.PMUXEN = 1;
    pport->Group[0].PINCFG[25].bit.PMUXEN = 1;
    pport->Group[1].PMUX[11].bit.PMUXE    = 7;  // PB22, function column H for USB SOF_1KHz output
    pport->Group[1].PINCFG[22].bit.PMUXEN = 1;

    // configure and enable DFLL for USB clock recovery mode at 48MHz
    posc->DFLLCTRLA.bit.ENABLE = 0;
    while (posc->DFLLSYNC.bit.ENABLE)
        ;
    while (posc->DFLLSYNC.bit.DFLLCTRLB)
        ;
    posc->DFLLCTRLB.bit.USBCRM = 1;
    while (posc->DFLLSYNC.bit.DFLLCTRLB)
        ;
    posc->DFLLCTRLB.bit.MODE = 1;
    while (posc->DFLLSYNC.bit.DFLLCTRLB)
        ;
    posc->DFLLCTRLB.bit.QLDIS = 0;
    while (posc->DFLLSYNC.bit.DFLLCTRLB)
        ;
    posc->DFLLCTRLB.bit.CCDIS = 1;
    posc->DFLLMUL.bit.MUL     = 0xbb80;  // 4800 x 1KHz
    while (posc->DFLLSYNC.bit.DFLLMUL)
        ;
    posc->DFLLCTRLA.bit.ENABLE = 1;
    while (posc->DFLLSYNC.bit.ENABLE)
        ;

    /* Setup clock for module */
    pgclk->PCHCTRL[GCLK_USB].bit.GEN  = 0;
    pgclk->PCHCTRL[GCLK_USB].bit.CHEN = 1;

    /* Reset */
    hw->DEVICE.CTRLA.bit.SWRST = 1;
    while (hw->DEVICE.SYNCBUSY.bit.SWRST) {
        /* Sync wait */
    }

    /* Change QOS values to have the best performance and correct USB behaviour */
    USB->DEVICE.QOSCTRL.bit.CQOS = 2;
    USB->DEVICE.QOSCTRL.bit.DQOS = 2;

    /* Load Pad Calibration */

    pad_transn = (USB_FUSES_TRANSN_ADDR >> USB_FUSES_TRANSN_Pos) & USB_FUSES_TRANSN_Msk;
    if (pad_transn == 0x1F) {
        pad_transn = 5;
    }

    hw->DEVICE.PADCAL.bit.TRANSN = pad_transn;

    pad_transp = (USB_FUSES_TRANSP_ADDR >> USB_FUSES_TRANSP_Pos) & USB_FUSES_TRANSP_Msk;
    if (pad_transp == 0x1F) {
        pad_transp = 29;
    }

    hw->DEVICE.PADCAL.bit.TRANSP = pad_transp;

    pad_trim = (USB_FUSES_TRIM_ADDR >> USB_FUSES_TRIM_Pos) & USB_FUSES_TRIM_Msk;
    if (pad_trim == 0x07) {
        pad_trim = 3;
    }

    hw->DEVICE.PADCAL.bit.TRIM = pad_trim;

    /* Set the configuration */
    hw->DEVICE.CTRLA.bit.MODE     = module_config->select_host_mode;
    hw->DEVICE.CTRLA.bit.RUNSTDBY = module_config->run_in_standby;
    hw->DEVICE.DESCADD.reg        = (uint32_t)(&usb_descriptor_table.usb_endpoint_table[0]);
    if (USB_SPEED_FULL == module_config->speed_mode) {
        module_inst->hw->DEVICE.CTRLB.bit.SPDCONF = USB_DEVICE_CTRLB_SPDCONF_FS_Val;
    } else if (USB_SPEED_LOW == module_config->speed_mode) {
        module_inst->hw->DEVICE.CTRLB.bit.SPDCONF = USB_DEVICE_CTRLB_SPDCONF_LS_Val;
    }

    memset((uint8_t *)(&usb_descriptor_table.usb_endpoint_table[0]), 0, sizeof(usb_descriptor_table.usb_endpoint_table));

    /*  device callback related */
    for (i = 0; i < USB_DEVICE_CALLBACK_N; i++) {
        module_inst->device_callback[i] = NULL;
    }
    for (i = 0; i < USB_EPT_NUM; i++) {
        for (j = 0; j < USB_DEVICE_EP_CALLBACK_N; j++) {
            module_inst->device_endpoint_callback[i][j] = NULL;
        }
    }
    module_inst->device_registered_callback_mask = 0;
    module_inst->device_enabled_callback_mask    = 0;
    for (j = 0; j < USB_EPT_NUM; j++) {
        module_inst->device_endpoint_registered_callback_mask[j] = 0;
        module_inst->device_endpoint_enabled_callback_mask[j]    = 0;
    }

    /* Enable interrupts for this USB module */
    NVIC_EnableIRQ(USB_0_IRQn);
    NVIC_EnableIRQ(USB_2_IRQn);
    NVIC_EnableIRQ(USB_3_IRQn);

    return STATUS_OK;
}