#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int usbep_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_12__ {int /*<<< orphan*/ * setup; TYPE_2__** epc; TYPE_5__** in_params; } ;
typedef  TYPE_4__ USBDriver ;
struct TYPE_13__ {TYPE_3__* config; int /*<<< orphan*/  obqueue; } ;
struct TYPE_11__ {int /*<<< orphan*/  fixed_size; } ;
struct TYPE_10__ {scalar_t__ in_maxsize; TYPE_1__* in_state; } ;
struct TYPE_9__ {unsigned int txsize; } ;
typedef  TYPE_5__ QMKUSBDriver ;

/* Variables and functions */
 int /*<<< orphan*/  CHN_OUTPUT_EMPTY ; 
 int /*<<< orphan*/  chnAddFlagsI (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obqGetFullBufferI (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  obqReleaseEmptyBufferI (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osalSysLockFromISR () ; 
 int /*<<< orphan*/  osalSysUnlockFromISR () ; 
 int /*<<< orphan*/  usbStartTransmitI (TYPE_4__*,unsigned int,int /*<<< orphan*/ *,size_t) ; 

void qmkusbDataTransmitted(USBDriver *usbp, usbep_t ep) {
    uint8_t *     buf;
    size_t        n;
    QMKUSBDriver *qmkusbp = usbp->in_params[ep - 1U];

    if (qmkusbp == NULL) {
        return;
    }

    osalSysLockFromISR();

    /* Signaling that space is available in the output queue.*/
    chnAddFlagsI(qmkusbp, CHN_OUTPUT_EMPTY);

    /* Freeing the buffer just transmitted, if it was not a zero size packet.*/
    if (usbp->epc[ep]->in_state->txsize > 0U) {
        obqReleaseEmptyBufferI(&qmkusbp->obqueue);
    }

    /* Checking if there is a buffer ready for transmission.*/
    buf = obqGetFullBufferI(&qmkusbp->obqueue, &n);

    if (buf != NULL) {
        /* The endpoint cannot be busy, we are in the context of the callback,
           so it is safe to transmit without a check.*/
        usbStartTransmitI(usbp, ep, buf, n);
    } else if ((usbp->epc[ep]->in_state->txsize > 0U) && ((usbp->epc[ep]->in_state->txsize & ((size_t)usbp->epc[ep]->in_maxsize - 1U)) == 0U)) {
        /* Transmit zero sized packet in case the last one has maximum allowed
           size. Otherwise the recipient may expect more data coming soon and
           not return buffered data to app. See section 5.8.3 Bulk Transfer
           Packet Size Constraints of the USB Specification document.*/
        if (!qmkusbp->config->fixed_size) {
            usbStartTransmitI(usbp, ep, usbp->setup, 0);
        }

    } else {
        /* Nothing to transmit.*/
    }

    osalSysUnlockFromISR();
}