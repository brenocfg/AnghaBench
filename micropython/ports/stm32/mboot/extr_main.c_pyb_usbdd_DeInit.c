#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  pyb_usbdd_obj_t ;
struct TYPE_3__ {scalar_t__ pClassData; } ;
typedef  TYPE_1__ USBD_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  USBD_OK ; 

__attribute__((used)) static uint8_t pyb_usbdd_DeInit(USBD_HandleTypeDef *pdev, uint8_t cfgidx) {
    pyb_usbdd_obj_t *self = (pyb_usbdd_obj_t*)pdev->pClassData;
    (void)self;
    return USBD_OK;
}