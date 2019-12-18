#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int usbep_t ;
struct TYPE_8__ {TYPE_3__** out_params; } ;
typedef  TYPE_2__ USBDriver ;
struct TYPE_9__ {TYPE_1__* config; int /*<<< orphan*/  ibqueue; } ;
struct TYPE_7__ {int /*<<< orphan*/  bulk_out; int /*<<< orphan*/  usbp; } ;
typedef  TYPE_3__ QMKUSBDriver ;

/* Variables and functions */
 int /*<<< orphan*/  CHN_INPUT_AVAILABLE ; 
 int /*<<< orphan*/  chnAddFlagsI (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibqPostFullBufferI (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osalSysLockFromISR () ; 
 int /*<<< orphan*/  osalSysUnlockFromISR () ; 
 int /*<<< orphan*/  qmkusb_start_receive (TYPE_3__*) ; 
 int /*<<< orphan*/  usbGetReceiveTransactionSizeX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void qmkusbDataReceived(USBDriver *usbp, usbep_t ep) {
    QMKUSBDriver *qmkusbp = usbp->out_params[ep - 1U];
    if (qmkusbp == NULL) {
        return;
    }

    osalSysLockFromISR();

    /* Signaling that data is available in the input queue.*/
    chnAddFlagsI(qmkusbp, CHN_INPUT_AVAILABLE);

    /* Posting the filled buffer in the queue.*/
    ibqPostFullBufferI(&qmkusbp->ibqueue, usbGetReceiveTransactionSizeX(qmkusbp->config->usbp, qmkusbp->config->bulk_out));

    /* The endpoint cannot be busy, we are in the context of the callback,
       so a packet is in the buffer for sure. Trying to get a free buffer
       for the next transaction.*/
    (void)qmkusb_start_receive(qmkusbp);

    osalSysUnlockFromISR();
}