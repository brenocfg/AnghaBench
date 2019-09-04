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
struct TYPE_4__ {int /*<<< orphan*/  work; } ;
struct TYPE_3__ {int /*<<< orphan*/  work; } ;
struct axp288_chrg_info {TYPE_2__ cable; TYPE_1__ otg; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void axp288_charger_cancel_work(void *data)
{
	struct axp288_chrg_info *info = data;

	cancel_work_sync(&info->otg.work);
	cancel_work_sync(&info->cable.work);
}