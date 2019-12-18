#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int* cmd; } ;
struct lx6464es {int /*<<< orphan*/  msg_lock; TYPE_1__ rmh; } ;
typedef  enum stream_state_t { ____Placeholder_stream_state_t } stream_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_13_SET_STREAM_STATE ; 
 int PIPE_INFO_TO_CMD (int,int) ; 
 int /*<<< orphan*/  lx_message_init (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int lx_message_send_atomic (struct lx6464es*,TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int lx_stream_set_state(struct lx6464es *chip, u32 pipe,
			       int is_capture, enum stream_state_t state)
{
	int err;
	u32 pipe_cmd = PIPE_INFO_TO_CMD(is_capture, pipe);

	mutex_lock(&chip->msg_lock);
	lx_message_init(&chip->rmh, CMD_13_SET_STREAM_STATE);

	chip->rmh.cmd[0] |= pipe_cmd;
	chip->rmh.cmd[0] |= state;

	err = lx_message_send_atomic(chip, &chip->rmh);
	mutex_unlock(&chip->msg_lock);

	return err;
}