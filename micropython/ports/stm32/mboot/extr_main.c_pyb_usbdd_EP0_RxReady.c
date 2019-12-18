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
struct TYPE_4__ {int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  wLength; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; } ;
typedef  TYPE_1__ pyb_usbdd_obj_t ;
struct TYPE_5__ {scalar_t__ pClassData; } ;
typedef  TYPE_2__ USBD_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  USBD_OK ; 
 int /*<<< orphan*/  dfu_handle_rx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t pyb_usbdd_EP0_RxReady(USBD_HandleTypeDef *pdev) {
    pyb_usbdd_obj_t *self = (pyb_usbdd_obj_t*)pdev->pClassData;
    dfu_handle_rx(self->bRequest, self->wValue, self->wLength, self->rx_buf);
    return USBD_OK;
}