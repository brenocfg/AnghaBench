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
struct nfcsim {int up; int /*<<< orphan*/  nfc_digital_dev; int /*<<< orphan*/  recv_work; int /*<<< orphan*/  send_work; int /*<<< orphan*/  link_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nfcsim*) ; 
 int /*<<< orphan*/  nfc_digital_free_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_digital_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfcsim_link_shutdown (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfcsim_device_free(struct nfcsim *dev)
{
	nfc_digital_unregister_device(dev->nfc_digital_dev);

	dev->up = false;

	nfcsim_link_shutdown(dev->link_in);

	cancel_delayed_work_sync(&dev->send_work);
	cancel_work_sync(&dev->recv_work);

	nfc_digital_free_device(dev->nfc_digital_dev);

	kfree(dev);
}