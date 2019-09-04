#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int max_mah; } ;
struct ab8500_fg {TYPE_1__ bat_cap; int /*<<< orphan*/  dev; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,size_t,unsigned long) ; 
 size_t kstrtoul (char const*,int,unsigned long*) ; 

__attribute__((used)) static ssize_t charge_full_store(struct ab8500_fg *di, const char *buf,
				 size_t count)
{
	unsigned long charge_full;
	ssize_t ret;

	ret = kstrtoul(buf, 10, &charge_full);

	dev_dbg(di->dev, "Ret %zd charge_full %lu", ret, charge_full);

	if (!ret) {
		di->bat_cap.max_mah = (int) charge_full;
		ret = count;
	}
	return ret;
}