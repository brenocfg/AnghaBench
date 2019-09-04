#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usbatm_vcc_data {int /*<<< orphan*/ * sarb; int /*<<< orphan*/  list; } ;
struct TYPE_4__ {int /*<<< orphan*/  tasklet; } ;
struct usbatm_data {int /*<<< orphan*/  serialize; TYPE_2__ rx_channel; void* cached_vci; void* cached_vpi; struct usbatm_vcc_data* cached_vcc; } ;
struct atm_vcc {int /*<<< orphan*/  flags; void* vci; void* vpi; struct usbatm_vcc_data* dev_data; TYPE_1__* dev; } ;
struct TYPE_3__ {struct usbatm_data* dev_data; } ;

/* Variables and functions */
 void* ATM_VCI_UNSPEC ; 
 int /*<<< orphan*/  ATM_VF_ADDR ; 
 int /*<<< orphan*/  ATM_VF_PARTIAL ; 
 int /*<<< orphan*/  ATM_VF_READY ; 
 void* ATM_VPI_UNSPEC ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct usbatm_vcc_data*) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbatm_cancel_send (struct usbatm_data*,struct atm_vcc*) ; 

__attribute__((used)) static void usbatm_atm_close(struct atm_vcc *vcc)
{
	struct usbatm_data *instance = vcc->dev->dev_data;
	struct usbatm_vcc_data *vcc_data = vcc->dev_data;

	if (!instance || !vcc_data)
		return;

	usbatm_cancel_send(instance, vcc);

	mutex_lock(&instance->serialize);	/* vs self, usbatm_atm_open, usbatm_usb_disconnect */

	tasklet_disable(&instance->rx_channel.tasklet);
	if (instance->cached_vcc == vcc_data) {
		instance->cached_vcc = NULL;
		instance->cached_vpi = ATM_VPI_UNSPEC;
		instance->cached_vci = ATM_VCI_UNSPEC;
	}
	list_del(&vcc_data->list);
	tasklet_enable(&instance->rx_channel.tasklet);

	kfree_skb(vcc_data->sarb);
	vcc_data->sarb = NULL;

	kfree(vcc_data);
	vcc->dev_data = NULL;

	vcc->vpi = ATM_VPI_UNSPEC;
	vcc->vci = ATM_VCI_UNSPEC;
	clear_bit(ATM_VF_READY, &vcc->flags);
	clear_bit(ATM_VF_PARTIAL, &vcc->flags);
	clear_bit(ATM_VF_ADDR, &vcc->flags);

	mutex_unlock(&instance->serialize);
}