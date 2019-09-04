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
typedef  int u32 ;
struct tsens_sensor {int /*<<< orphan*/  status; } ;
struct tsens_device {int /*<<< orphan*/  map; struct tsens_sensor* sensor; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  INT_STATUS_ADDR ; 
 int /*<<< orphan*/  TIMEOUT_US ; 
 int TRDY_MASK ; 
 int code_to_mdegC (int,struct tsens_sensor const*) ; 
 unsigned long jiffies ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 unsigned long usecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_temp_8960(struct tsens_device *tmdev, int id, int *temp)
{
	int ret;
	u32 code, trdy;
	const struct tsens_sensor *s = &tmdev->sensor[id];
	unsigned long timeout;

	timeout = jiffies + usecs_to_jiffies(TIMEOUT_US);
	do {
		ret = regmap_read(tmdev->map, INT_STATUS_ADDR, &trdy);
		if (ret)
			return ret;
		if (!(trdy & TRDY_MASK))
			continue;
		ret = regmap_read(tmdev->map, s->status, &code);
		if (ret)
			return ret;
		*temp = code_to_mdegC(code, s);
		return 0;
	} while (time_before(jiffies, timeout));

	return -ETIMEDOUT;
}