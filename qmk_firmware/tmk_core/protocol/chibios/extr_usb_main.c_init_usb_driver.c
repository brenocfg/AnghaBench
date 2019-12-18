#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USBDriver ;
struct TYPE_10__ {TYPE_4__* array; } ;
struct TYPE_8__ {int /*<<< orphan*/ * in_state; } ;
struct TYPE_7__ {int /*<<< orphan*/ * out_state; } ;
struct TYPE_6__ {int /*<<< orphan*/ * in_state; } ;
struct TYPE_9__ {int /*<<< orphan*/  config; int /*<<< orphan*/  int_ep_state; TYPE_3__ int_ep_config; int /*<<< orphan*/  out_ep_state; TYPE_2__ out_ep_config; int /*<<< orphan*/  in_ep_state; TYPE_1__ in_ep_config; int /*<<< orphan*/  driver; } ;
typedef  int /*<<< orphan*/  QMKUSBDriver ;

/* Variables and functions */
 int NUM_USB_DRIVERS ; 
 int /*<<< orphan*/  chVTObjectInit (int /*<<< orphan*/ *) ; 
 TYPE_5__ drivers ; 
 int /*<<< orphan*/  keyboard_idle_timer ; 
 int /*<<< orphan*/  qmkusbObjectInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qmkusbStart (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbConnectBus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbDisconnectBus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbStart (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbcfg ; 
 int /*<<< orphan*/  wait_ms (int) ; 

void init_usb_driver(USBDriver *usbp) {
    for (int i = 0; i < NUM_USB_DRIVERS; i++) {
        QMKUSBDriver *driver                     = &drivers.array[i].driver;
        drivers.array[i].in_ep_config.in_state   = &drivers.array[i].in_ep_state;
        drivers.array[i].out_ep_config.out_state = &drivers.array[i].out_ep_state;
        drivers.array[i].int_ep_config.in_state  = &drivers.array[i].int_ep_state;
        qmkusbObjectInit(driver, &drivers.array[i].config);
        qmkusbStart(driver, &drivers.array[i].config);
    }

    /*
     * Activates the USB driver and then the USB bus pull-up on D+.
     * Note, a delay is inserted in order to not have to disconnect the cable
     * after a reset.
     */
    usbDisconnectBus(usbp);
    wait_ms(1500);
    usbStart(usbp, &usbcfg);
    usbConnectBus(usbp);

    chVTObjectInit(&keyboard_idle_timer);
}