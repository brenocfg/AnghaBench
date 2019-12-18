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
typedef  int /*<<< orphan*/  io_buffers_queue_t ;
struct TYPE_5__ {scalar_t__ state; TYPE_1__* config; int /*<<< orphan*/  obqueue; } ;
struct TYPE_4__ {int /*<<< orphan*/  bulk_in; int /*<<< orphan*/  usbp; } ;
typedef  TYPE_2__ QMKUSBDriver ;

/* Variables and functions */
 scalar_t__ QMKUSB_READY ; 
 scalar_t__ USB_ACTIVE ; 
 TYPE_2__* bqGetLinkX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obqGetFullBufferI (int /*<<< orphan*/ *,size_t*) ; 
 scalar_t__ usbGetDriverStateI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbGetTransmitStatusI (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbStartTransmitI (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void obnotify(io_buffers_queue_t *bqp) {
    size_t        n;
    QMKUSBDriver *qmkusbp = bqGetLinkX(bqp);

    /* If the USB driver is not in the appropriate state then transactions
       must not be started.*/
    if ((usbGetDriverStateI(qmkusbp->config->usbp) != USB_ACTIVE) || (qmkusbp->state != QMKUSB_READY)) {
        return;
    }

    /* Checking if there is already a transaction ongoing on the endpoint.*/
    if (!usbGetTransmitStatusI(qmkusbp->config->usbp, qmkusbp->config->bulk_in)) {
        /* Trying to get a full buffer.*/
        uint8_t *buf = obqGetFullBufferI(&qmkusbp->obqueue, &n);
        if (buf != NULL) {
            /* Buffer found, starting a new transaction.*/
            usbStartTransmitI(qmkusbp->config->usbp, qmkusbp->config->bulk_in, buf, n);
        }
    }
}