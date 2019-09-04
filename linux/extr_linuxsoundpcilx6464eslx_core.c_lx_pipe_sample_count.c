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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {int stat_len; int* stat; int /*<<< orphan*/ * cmd; } ;
struct lx6464es {int /*<<< orphan*/  msg_lock; TYPE_2__ rmh; TYPE_1__* card; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_0A_GET_PIPE_SPL_COUNT ; 
 int MASK_SPL_COUNT_HI ; 
 int /*<<< orphan*/  PIPE_INFO_TO_CMD (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lx_message_init (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int lx_message_send_atomic (struct lx6464es*,TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int lx_pipe_sample_count(struct lx6464es *chip, u32 pipe, int is_capture,
			 u64 *rsample_count)
{
	int err;
	u32 pipe_cmd = PIPE_INFO_TO_CMD(is_capture, pipe);

	mutex_lock(&chip->msg_lock);
	lx_message_init(&chip->rmh, CMD_0A_GET_PIPE_SPL_COUNT);

	chip->rmh.cmd[0] |= pipe_cmd;
	chip->rmh.stat_len = 2;	/* need all words here! */

	err = lx_message_send_atomic(chip, &chip->rmh); /* don't sleep! */

	if (err != 0)
		dev_err(chip->card->dev,
			"could not query pipe's sample count\n");
	else {
		*rsample_count = ((u64)(chip->rmh.stat[0] & MASK_SPL_COUNT_HI)
				  << 24)     /* hi part */
			+ chip->rmh.stat[1]; /* lo part */
	}

	mutex_unlock(&chip->msg_lock);
	return err;
}