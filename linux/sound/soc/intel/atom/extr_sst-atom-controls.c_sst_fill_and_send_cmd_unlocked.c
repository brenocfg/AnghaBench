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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sst_data {int /*<<< orphan*/  byte_stream; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; TYPE_1__* ops; } ;
struct TYPE_3__ {int (* send_byte_stream ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_2__* sst ; 
 int sst_fill_byte_control (struct sst_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sst_fill_and_send_cmd_unlocked(struct sst_data *drv,
				 u8 ipc_msg, u8 block, u8 task_id, u8 pipe_id,
				 void *cmd_data, u16 len)
{
	int ret = 0;

	ret = sst_fill_byte_control(drv, ipc_msg,
				block, task_id, pipe_id, len, cmd_data);
	if (ret < 0)
		return ret;
	return sst->ops->send_byte_stream(sst->dev, drv->byte_stream);
}