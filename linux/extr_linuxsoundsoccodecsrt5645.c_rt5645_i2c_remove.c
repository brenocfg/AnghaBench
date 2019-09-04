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
struct rt5645_priv {int /*<<< orphan*/  supplies; int /*<<< orphan*/  btn_check_timer; int /*<<< orphan*/  rcclock_work; int /*<<< orphan*/  jack_detect_work; } ;
struct i2c_client {scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct rt5645_priv*) ; 
 struct rt5645_priv* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt5645_i2c_remove(struct i2c_client *i2c)
{
	struct rt5645_priv *rt5645 = i2c_get_clientdata(i2c);

	if (i2c->irq)
		free_irq(i2c->irq, rt5645);

	cancel_delayed_work_sync(&rt5645->jack_detect_work);
	cancel_delayed_work_sync(&rt5645->rcclock_work);
	del_timer_sync(&rt5645->btn_check_timer);

	regulator_bulk_disable(ARRAY_SIZE(rt5645->supplies), rt5645->supplies);

	return 0;
}