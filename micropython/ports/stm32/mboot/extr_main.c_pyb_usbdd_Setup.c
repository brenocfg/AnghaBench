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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {int tx_pending; int /*<<< orphan*/  tx_buf; int /*<<< orphan*/  hUSBDDevice; int /*<<< orphan*/  wLength; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  rx_buf; } ;
typedef  TYPE_1__ pyb_usbdd_obj_t ;
struct TYPE_8__ {int bmRequest; int /*<<< orphan*/  wLength; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; } ;
typedef  TYPE_2__ USBD_SetupReqTypedef ;
struct TYPE_9__ {scalar_t__ pClassData; } ;
typedef  TYPE_3__ USBD_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  USBD_CtlPrepareRx (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBD_CtlSendData (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  USBD_OK ; 
 int /*<<< orphan*/  USB_XFER_SIZE ; 
 int /*<<< orphan*/  dfu_handle_rx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int dfu_handle_tx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t pyb_usbdd_Setup(USBD_HandleTypeDef *pdev, USBD_SetupReqTypedef *req) {
    pyb_usbdd_obj_t *self = (pyb_usbdd_obj_t*)pdev->pClassData;
    (void)self;
    self->bRequest = req->bRequest;
    self->wValue = req->wValue;
    self->wLength = req->wLength;
    if (req->bmRequest == 0x21) {
        // host-to-device request
        if (req->wLength == 0) {
            // no data, process command straightaway
            dfu_handle_rx(self->bRequest, self->wValue, 0, NULL);
        } else {
            // have data, prepare to receive it
            USBD_CtlPrepareRx(pdev, self->rx_buf, req->wLength);
        }
    } else if (req->bmRequest == 0xa1) {
        // device-to-host request
        int len = dfu_handle_tx(self->bRequest, self->wValue, self->wLength, self->tx_buf, USB_XFER_SIZE);
        if (len >= 0) {
            self->tx_pending = true;
            USBD_CtlSendData(&self->hUSBDDevice, self->tx_buf, len);
        }
    }
    return USBD_OK;
}