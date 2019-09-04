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
typedef  int u32 ;
struct qoriq_tmu_data {size_t sensor_id; TYPE_2__* regs; } ;
struct TYPE_4__ {TYPE_1__* site; } ;
struct TYPE_3__ {int /*<<< orphan*/  tritsr; } ;

/* Variables and functions */
 int tmu_read (struct qoriq_tmu_data*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tmu_get_temp(void *p, int *temp)
{
	u32 val;
	struct qoriq_tmu_data *data = p;

	val = tmu_read(data, &data->regs->site[data->sensor_id].tritsr);
	*temp = (val & 0xff) * 1000;

	return 0;
}