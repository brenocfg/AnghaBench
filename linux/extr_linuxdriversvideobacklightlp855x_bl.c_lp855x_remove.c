#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct lp855x {TYPE_2__* dev; scalar_t__ supply; TYPE_3__* bl; } ;
struct i2c_client {int dummy; } ;
struct TYPE_4__ {scalar_t__ brightness; } ;
struct TYPE_6__ {TYPE_1__ props; } ;
struct TYPE_5__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  backlight_update_status (TYPE_3__*) ; 
 struct lp855x* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  lp855x_attr_group ; 
 int /*<<< orphan*/  regulator_disable (scalar_t__) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lp855x_remove(struct i2c_client *cl)
{
	struct lp855x *lp = i2c_get_clientdata(cl);

	lp->bl->props.brightness = 0;
	backlight_update_status(lp->bl);
	if (lp->supply)
		regulator_disable(lp->supply);
	sysfs_remove_group(&lp->dev->kobj, &lp855x_attr_group);

	return 0;
}