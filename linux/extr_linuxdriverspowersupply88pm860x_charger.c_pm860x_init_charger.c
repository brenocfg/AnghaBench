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
struct pm860x_charger_info {int online; int allowed; int /*<<< orphan*/  lock; int /*<<< orphan*/  state; int /*<<< orphan*/  i2c; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSM_INIT ; 
 int /*<<< orphan*/  PM8607_STATUS_2 ; 
 int STATUS2_CHG ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pm860x_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_charging_fsm (struct pm860x_charger_info*) ; 

__attribute__((used)) static int pm860x_init_charger(struct pm860x_charger_info *info)
{
	int ret;

	ret = pm860x_reg_read(info->i2c, PM8607_STATUS_2);
	if (ret < 0)
		return ret;

	mutex_lock(&info->lock);
	info->state = FSM_INIT;
	if (ret & STATUS2_CHG) {
		info->online = 1;
		info->allowed = 1;
	} else {
		info->online = 0;
		info->allowed = 0;
	}
	mutex_unlock(&info->lock);

	set_charging_fsm(info);
	return 0;
}