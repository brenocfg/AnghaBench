#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {scalar_t__ state; TYPE_1__* config; int /*<<< orphan*/  obqueue; } ;
struct TYPE_4__ {size_t in_size; int /*<<< orphan*/  bulk_in; int /*<<< orphan*/  usbp; scalar_t__ fixed_size; } ;
typedef  TYPE_2__ QMKUSBDriver ;

/* Variables and functions */
 scalar_t__ QMKUSB_READY ; 
 scalar_t__ USB_ACTIVE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/ * obqGetFullBufferI (int /*<<< orphan*/ *,size_t*) ; 
 scalar_t__ obqTryFlushI (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osalDbgAssert (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ usbGetDriverStateI (int /*<<< orphan*/ ) ; 
 scalar_t__ usbGetTransmitStatusI (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbStartTransmitI (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

void qmkusbSOFHookI(QMKUSBDriver *qmkusbp) {
    /* If the USB driver is not in the appropriate state then transactions
       must not be started.*/
    if ((usbGetDriverStateI(qmkusbp->config->usbp) != USB_ACTIVE) || (qmkusbp->state != QMKUSB_READY)) {
        return;
    }

    /* If there is already a transaction ongoing then another one cannot be
       started.*/
    if (usbGetTransmitStatusI(qmkusbp->config->usbp, qmkusbp->config->bulk_in)) {
        return;
    }

    /* Checking if there only a buffer partially filled, if so then it is
       enforced in the queue and transmitted.*/
    if (obqTryFlushI(&qmkusbp->obqueue)) {
        size_t   n;
        uint8_t *buf = obqGetFullBufferI(&qmkusbp->obqueue, &n);

        /* For fixed size drivers, fill the end with zeros */
        if (qmkusbp->config->fixed_size) {
            memset(buf + n, 0, qmkusbp->config->in_size - n);
            n = qmkusbp->config->in_size;
        }

        osalDbgAssert(buf != NULL, "queue is empty");

        usbStartTransmitI(qmkusbp->config->usbp, qmkusbp->config->bulk_in, buf, n);
    }
}