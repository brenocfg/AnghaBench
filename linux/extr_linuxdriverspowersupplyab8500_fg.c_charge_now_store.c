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
struct TYPE_3__ {int user_cap; } ;
struct TYPE_4__ {int user_mah; int /*<<< orphan*/  prev_mah; } ;
struct ab8500_fg {int /*<<< orphan*/  fg_periodic_work; int /*<<< orphan*/  fg_wq; TYPE_1__ flags; TYPE_2__ bat_cap; int /*<<< orphan*/  dev; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,size_t,unsigned long,int /*<<< orphan*/ ) ; 
 size_t kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t charge_now_store(struct ab8500_fg *di, const char *buf,
				 size_t count)
{
	unsigned long charge_now;
	ssize_t ret;

	ret = kstrtoul(buf, 10, &charge_now);

	dev_dbg(di->dev, "Ret %zd charge_now %lu was %d",
		ret, charge_now, di->bat_cap.prev_mah);

	if (!ret) {
		di->bat_cap.user_mah = (int) charge_now;
		di->flags.user_cap = true;
		ret = count;
		queue_delayed_work(di->fg_wq, &di->fg_periodic_work, 0);
	}
	return ret;
}