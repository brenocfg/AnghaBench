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
typedef  int u32 ;
struct TYPE_5__ {int* cmd; } ;
struct lx6464es {TYPE_1__* card; int /*<<< orphan*/  msg_lock; TYPE_2__ rmh; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_06_ALLOCATE_PIPE ; 
 int PIPE_INFO_TO_CMD (int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lx_message_init (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int lx_message_send_atomic (struct lx6464es*,TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int lx_pipe_allocate(struct lx6464es *chip, u32 pipe, int is_capture,
		     int channels)
{
	int err;
	u32 pipe_cmd = PIPE_INFO_TO_CMD(is_capture, pipe);

	mutex_lock(&chip->msg_lock);
	lx_message_init(&chip->rmh, CMD_06_ALLOCATE_PIPE);

	chip->rmh.cmd[0] |= pipe_cmd;
	chip->rmh.cmd[0] |= channels;

	err = lx_message_send_atomic(chip, &chip->rmh);
	mutex_unlock(&chip->msg_lock);

	if (err != 0)
		dev_err(chip->card->dev, "could not allocate pipe\n");

	return err;
}