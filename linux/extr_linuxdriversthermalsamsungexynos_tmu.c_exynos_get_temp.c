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
struct exynos_tmu_data {int (* tmu_read ) (struct exynos_tmu_data*) ;int /*<<< orphan*/  lock; int /*<<< orphan*/  clk; int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int MCELSIUS ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int code_to_temp (struct exynos_tmu_data*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct exynos_tmu_data*) ; 

__attribute__((used)) static int exynos_get_temp(void *p, int *temp)
{
	struct exynos_tmu_data *data = p;
	int value, ret = 0;

	if (!data || !data->tmu_read)
		return -EINVAL;
	else if (!data->enabled)
		/*
		 * Called too early, probably
		 * from thermal_zone_of_sensor_register().
		 */
		return -EAGAIN;

	mutex_lock(&data->lock);
	clk_enable(data->clk);

	value = data->tmu_read(data);
	if (value < 0)
		ret = value;
	else
		*temp = code_to_temp(data, value) * MCELSIUS;

	clk_disable(data->clk);
	mutex_unlock(&data->lock);

	return ret;
}