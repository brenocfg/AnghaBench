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
typedef  int u8 ;
struct mid_pb_ddata {int pbstat_mask; int /*<<< orphan*/  pbstat_addr; struct input_dev* input; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct input_dev {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int intel_scu_ipc_ioread8 (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int mid_pbstat(struct mid_pb_ddata *ddata, int *value)
{
	struct input_dev *input = ddata->input;
	int ret;
	u8 pbstat;

	ret = intel_scu_ipc_ioread8(ddata->pbstat_addr, &pbstat);
	if (ret)
		return ret;

	dev_dbg(input->dev.parent, "PB_INT status= %d\n", pbstat);

	*value = !(pbstat & ddata->pbstat_mask);
	return 0;
}