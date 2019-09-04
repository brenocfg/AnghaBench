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
struct o2hb_region {int /*<<< orphan*/  hr_nego_timeout_work; int /*<<< orphan*/  hr_write_timeout_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void o2hb_disarm_timeout(struct o2hb_region *reg)
{
	cancel_delayed_work_sync(&reg->hr_write_timeout_work);
	cancel_delayed_work_sync(&reg->hr_nego_timeout_work);
}