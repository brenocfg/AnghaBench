#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct nkro_report {int dummy; } ;
struct TYPE_13__ {int mods; } ;
typedef  TYPE_3__ report_keyboard_t ;
struct TYPE_15__ {scalar_t__ nkro; } ;
struct TYPE_14__ {TYPE_2__** epc; } ;
struct TYPE_12__ {TYPE_1__* in_state; } ;
struct TYPE_11__ {int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 size_t KEYBOARD_IN_EPNUM ; 
 int KEYBOARD_REPORT_SIZE ; 
 size_t SHARED_IN_EPNUM ; 
 scalar_t__ USB_ACTIVE ; 
 TYPE_4__ USB_DRIVER ; 
 scalar_t__ keyboard_protocol ; 
 TYPE_3__ keyboard_report_sent ; 
 TYPE_8__ keymap_config ; 
 int /*<<< orphan*/  osalSysLock () ; 
 int /*<<< orphan*/  osalSysUnlock () ; 
 int /*<<< orphan*/  osalThreadSuspendS (int /*<<< orphan*/ *) ; 
 scalar_t__ usbGetDriverStateI (TYPE_4__*) ; 
 scalar_t__ usbGetTransmitStatusI (TYPE_4__*,size_t) ; 
 int /*<<< orphan*/  usbStartTransmitI (TYPE_4__*,size_t,int*,int) ; 

void send_keyboard(report_keyboard_t *report) {
    osalSysLock();
    if (usbGetDriverStateI(&USB_DRIVER) != USB_ACTIVE) {
        osalSysUnlock();
        return;
    }
    osalSysUnlock();

#ifdef NKRO_ENABLE
    if (keymap_config.nkro && keyboard_protocol) { /* NKRO protocol */
        /* need to wait until the previous packet has made it through */
        /* can rewrite this using the synchronous API, then would wait
         * until *after* the packet has been transmitted. I think
         * this is more efficient */
        /* busy wait, should be short and not very common */
        osalSysLock();
        if (usbGetTransmitStatusI(&USB_DRIVER, SHARED_IN_EPNUM)) {
            /* Need to either suspend, or loop and call unlock/lock during
             * every iteration - otherwise the system will remain locked,
             * no interrupts served, so USB not going through as well.
             * Note: for suspend, need USB_USE_WAIT == TRUE in halconf.h */
            osalThreadSuspendS(&(&USB_DRIVER)->epc[SHARED_IN_EPNUM]->in_state->thread);
        }
        usbStartTransmitI(&USB_DRIVER, SHARED_IN_EPNUM, (uint8_t *)report, sizeof(struct nkro_report));
        osalSysUnlock();
    } else
#endif /* NKRO_ENABLE */
    {  /* regular protocol */
        /* need to wait until the previous packet has made it through */
        /* busy wait, should be short and not very common */
        osalSysLock();
        if (usbGetTransmitStatusI(&USB_DRIVER, KEYBOARD_IN_EPNUM)) {
            /* Need to either suspend, or loop and call unlock/lock during
             * every iteration - otherwise the system will remain locked,
             * no interrupts served, so USB not going through as well.
             * Note: for suspend, need USB_USE_WAIT == TRUE in halconf.h */
            osalThreadSuspendS(&(&USB_DRIVER)->epc[KEYBOARD_IN_EPNUM]->in_state->thread);
        }
        uint8_t *data, size;
        if (keyboard_protocol) {
            data = (uint8_t *)report;
            size = KEYBOARD_REPORT_SIZE;
        } else { /* boot protocol */
            data = &report->mods;
            size = 8;
        }
        usbStartTransmitI(&USB_DRIVER, KEYBOARD_IN_EPNUM, data, size);
        osalSysUnlock();
    }
    keyboard_report_sent = *report;
}