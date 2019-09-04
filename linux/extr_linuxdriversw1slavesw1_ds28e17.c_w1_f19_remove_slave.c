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
struct w1_slave {struct w1_f19_data* family_data; int /*<<< orphan*/  dev; } ;
struct w1_f19_data {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,struct w1_f19_data*) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void w1_f19_remove_slave(struct w1_slave *sl)
{
	struct w1_f19_data *family_data = sl->family_data;

	/* Delete I2C adapter. */
	i2c_del_adapter(&family_data->adapter);

	/* Free slave specific data. */
	devm_kfree(&sl->dev, family_data);
	sl->family_data = NULL;
}