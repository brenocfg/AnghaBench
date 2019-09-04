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
struct nfc_digital_dev {int /*<<< orphan*/  poll_work; int /*<<< orphan*/  poll_lock; scalar_t__ poll_tech_count; } ;
struct nfc_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  digital_abort_cmd (struct nfc_digital_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct nfc_digital_dev* nfc_get_drvdata (struct nfc_dev*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static void digital_stop_poll(struct nfc_dev *nfc_dev)
{
	struct nfc_digital_dev *ddev = nfc_get_drvdata(nfc_dev);

	mutex_lock(&ddev->poll_lock);

	if (!ddev->poll_tech_count) {
		pr_err("Polling operation was not running\n");
		mutex_unlock(&ddev->poll_lock);
		return;
	}

	ddev->poll_tech_count = 0;

	mutex_unlock(&ddev->poll_lock);

	cancel_delayed_work_sync(&ddev->poll_work);

	digital_abort_cmd(ddev);
}