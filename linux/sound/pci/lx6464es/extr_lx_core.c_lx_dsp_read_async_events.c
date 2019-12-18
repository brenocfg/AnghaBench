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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int stat_len; int /*<<< orphan*/  stat; } ;
struct lx6464es {int /*<<< orphan*/  msg_lock; TYPE_1__ rmh; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_04_GET_EVENT ; 
 int /*<<< orphan*/  lx_message_init (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int lx_message_send_atomic (struct lx6464es*,TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int lx_dsp_read_async_events(struct lx6464es *chip, u32 *data)
{
	int ret;

	mutex_lock(&chip->msg_lock);

	lx_message_init(&chip->rmh, CMD_04_GET_EVENT);
	chip->rmh.stat_len = 9;	/* we don't necessarily need the full length */

	ret = lx_message_send_atomic(chip, &chip->rmh);

	if (!ret)
		memcpy(data, chip->rmh.stat, chip->rmh.stat_len * sizeof(u32));

	mutex_unlock(&chip->msg_lock);
	return ret;
}