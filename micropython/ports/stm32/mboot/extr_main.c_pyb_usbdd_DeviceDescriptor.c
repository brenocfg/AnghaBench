#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  USBD_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  USB_LEN_DEV_DESC ; 
 scalar_t__ dev_descr ; 

__attribute__((used)) static uint8_t *pyb_usbdd_DeviceDescriptor(USBD_HandleTypeDef *pdev, uint16_t *length) {
    *length = USB_LEN_DEV_DESC;
    return (uint8_t*)dev_descr;
}