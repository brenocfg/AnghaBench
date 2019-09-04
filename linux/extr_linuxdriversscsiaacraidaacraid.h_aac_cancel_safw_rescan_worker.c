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
struct aac_dev {int /*<<< orphan*/  safw_rescan_work; scalar_t__ sa_firmware; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void aac_cancel_safw_rescan_worker(struct aac_dev *dev)
{
	if (dev->sa_firmware)
		cancel_delayed_work_sync(&dev->safw_rescan_work);
}