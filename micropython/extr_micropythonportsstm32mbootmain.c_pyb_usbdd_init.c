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
struct TYPE_5__ {int id; TYPE_1__* pClassData; int /*<<< orphan*/ * pClass; int /*<<< orphan*/ * pDesc; int /*<<< orphan*/  dev_state; } ;
struct TYPE_4__ {int started; int tx_pending; TYPE_2__ hUSBDDevice; } ;
typedef  TYPE_1__ pyb_usbdd_obj_t ;
typedef  TYPE_2__ USBD_HandleTypeDef ;
typedef  int /*<<< orphan*/  USBD_DescriptorsTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  USBD_STATE_DEFAULT ; 
 int /*<<< orphan*/  pyb_usbdd_class ; 
 int /*<<< orphan*/  pyb_usbdd_descriptors ; 

__attribute__((used)) static void pyb_usbdd_init(pyb_usbdd_obj_t *self, int phy_id) {
    self->started = false;
    self->tx_pending = false;
    USBD_HandleTypeDef *usbd = &self->hUSBDDevice;
    usbd->id = phy_id;
    usbd->dev_state = USBD_STATE_DEFAULT;
    usbd->pDesc = (USBD_DescriptorsTypeDef*)&pyb_usbdd_descriptors;
    usbd->pClass = &pyb_usbdd_class;
    usbd->pClassData = self;
}