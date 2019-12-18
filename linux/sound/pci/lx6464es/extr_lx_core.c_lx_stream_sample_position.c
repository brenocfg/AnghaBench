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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int* stat; int /*<<< orphan*/ * cmd; } ;
struct lx6464es {int /*<<< orphan*/  msg_lock; TYPE_1__ rmh; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_0E_GET_STREAM_SPL_COUNT ; 
 int MASK_SPL_COUNT_HI ; 
 int /*<<< orphan*/  PIPE_INFO_TO_CMD (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lx_message_init (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int lx_message_send_atomic (struct lx6464es*,TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int lx_stream_sample_position(struct lx6464es *chip, u32 pipe, int is_capture,
			      u64 *r_bytepos)
{
	int err;
	u32 pipe_cmd = PIPE_INFO_TO_CMD(is_capture, pipe);

	mutex_lock(&chip->msg_lock);
	lx_message_init(&chip->rmh, CMD_0E_GET_STREAM_SPL_COUNT);

	chip->rmh.cmd[0] |= pipe_cmd;

	err = lx_message_send_atomic(chip, &chip->rmh);

	*r_bytepos = ((u64) (chip->rmh.stat[0] & MASK_SPL_COUNT_HI)
		      << 32)	     /* hi part */
		+ chip->rmh.stat[1]; /* lo part */

	mutex_unlock(&chip->msg_lock);
	return err;
}