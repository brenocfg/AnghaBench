#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {scalar_t__ bsize; } ;
struct TYPE_6__ {scalar_t__ state; TYPE_4__ ibqueue; TYPE_1__* config; } ;
struct TYPE_5__ {int /*<<< orphan*/  bulk_out; int /*<<< orphan*/  usbp; int /*<<< orphan*/  bulk_in; } ;
typedef  TYPE_2__ QMKUSBDriver ;

/* Variables and functions */
 scalar_t__ QMKUSB_READY ; 
 scalar_t__ USB_ACTIVE ; 
 int /*<<< orphan*/ * ibqGetEmptyBufferI (TYPE_4__*) ; 
 scalar_t__ usbGetDriverStateI (int /*<<< orphan*/ ) ; 
 scalar_t__ usbGetReceiveStatusI (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbStartReceiveI (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static bool qmkusb_start_receive(QMKUSBDriver *qmkusbp) {
    uint8_t *buf;

    /* If the USB driver is not in the appropriate state then transactions
       must not be started.*/
    if ((usbGetDriverStateI(qmkusbp->config->usbp) != USB_ACTIVE) || (qmkusbp->state != QMKUSB_READY)) {
        return true;
    }

    /* Checking if there is already a transaction ongoing on the endpoint.*/
    if (usbGetReceiveStatusI(qmkusbp->config->usbp, qmkusbp->config->bulk_in)) {
        return true;
    }

    /* Checking if there is a buffer ready for incoming data.*/
    buf = ibqGetEmptyBufferI(&qmkusbp->ibqueue);
    if (buf == NULL) {
        return true;
    }

    /* Buffer found, starting a new transaction.*/
    usbStartReceiveI(qmkusbp->config->usbp, qmkusbp->config->bulk_out, buf, qmkusbp->ibqueue.bsize - sizeof(size_t));

    return false;
}