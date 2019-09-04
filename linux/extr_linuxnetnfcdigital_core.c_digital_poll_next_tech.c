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
typedef  int u8 ;
struct nfc_digital_dev {int poll_tech_count; int poll_tech_index; int /*<<< orphan*/  poll_work; int /*<<< orphan*/  poll_lock; } ;
typedef  int /*<<< orphan*/  rand_mod ;

/* Variables and functions */
 int /*<<< orphan*/  DIGITAL_POLL_INTERVAL ; 
 int /*<<< orphan*/  digital_switch_rf (struct nfc_digital_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_random_bytes (int*,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void digital_poll_next_tech(struct nfc_digital_dev *ddev)
{
	u8 rand_mod;

	digital_switch_rf(ddev, 0);

	mutex_lock(&ddev->poll_lock);

	if (!ddev->poll_tech_count) {
		mutex_unlock(&ddev->poll_lock);
		return;
	}

	get_random_bytes(&rand_mod, sizeof(rand_mod));
	ddev->poll_tech_index = rand_mod % ddev->poll_tech_count;

	mutex_unlock(&ddev->poll_lock);

	schedule_delayed_work(&ddev->poll_work,
			      msecs_to_jiffies(DIGITAL_POLL_INTERVAL));
}