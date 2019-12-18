#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct TYPE_5__ {int* stat; int /*<<< orphan*/ * cmd; } ;
struct lx6464es {int /*<<< orphan*/  msg_lock; TYPE_2__ rmh; TYPE_1__* card; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_0A_GET_PIPE_SPL_COUNT ; 
 int /*<<< orphan*/  PIPE_INFO_TO_CMD (int,int /*<<< orphan*/ ) ; 
 int PSTATE_OFFSET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lx_message_init (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int lx_message_send_atomic (struct lx6464es*,TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int lx_pipe_state(struct lx6464es *chip, u32 pipe, int is_capture, u16 *rstate)
{
	int err;
	u32 pipe_cmd = PIPE_INFO_TO_CMD(is_capture, pipe);

	mutex_lock(&chip->msg_lock);
	lx_message_init(&chip->rmh, CMD_0A_GET_PIPE_SPL_COUNT);

	chip->rmh.cmd[0] |= pipe_cmd;

	err = lx_message_send_atomic(chip, &chip->rmh);

	if (err != 0)
		dev_err(chip->card->dev, "could not query pipe's state\n");
	else
		*rstate = (chip->rmh.stat[0] >> PSTATE_OFFSET) & 0x0F;

	mutex_unlock(&chip->msg_lock);
	return err;
}