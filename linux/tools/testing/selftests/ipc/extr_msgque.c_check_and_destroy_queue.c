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
struct msgque_data {int qnum; int /*<<< orphan*/  msq_id; TYPE_1__* messages; } ;
struct msg1 {scalar_t__ mtype; int /*<<< orphan*/  mtext; } ;
struct TYPE_2__ {int msize; scalar_t__ mtype; int /*<<< orphan*/  mtext; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMSG ; 
 int /*<<< orphan*/  IPC_NOWAIT ; 
 int /*<<< orphan*/  IPC_RMID ; 
 int /*<<< orphan*/  MAX_MSG_SIZE ; 
 int errno ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ msgctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int msgrcv (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int check_and_destroy_queue(struct msgque_data *msgque)
{
	struct msg1 message;
	int cnt = 0, ret;

	while (1) {
		ret = msgrcv(msgque->msq_id, &message.mtype, MAX_MSG_SIZE,
				0, IPC_NOWAIT);
		if (ret < 0) {
			if (errno == ENOMSG)
				break;
			printf("Failed to read IPC message: %m\n");
			ret = -errno;
			goto err;
		}
		if (ret != msgque->messages[cnt].msize) {
			printf("Wrong message size: %d (expected %d)\n", ret,
						msgque->messages[cnt].msize);
			ret = -EINVAL;
			goto err;
		}
		if (message.mtype != msgque->messages[cnt].mtype) {
			printf("Wrong message type\n");
			ret = -EINVAL;
			goto err;
		}
		if (memcmp(message.mtext, msgque->messages[cnt].mtext, ret)) {
			printf("Wrong message content\n");
			ret = -EINVAL;
			goto err;
		}
		cnt++;
	}

	if (cnt != msgque->qnum) {
		printf("Wrong message number\n");
		ret = -EINVAL;
		goto err;
	}

	ret = 0;
err:
	if (msgctl(msgque->msq_id, IPC_RMID, NULL)) {
		printf("Failed to destroy queue: %d\n", -errno);
		return -errno;
	}
	return ret;
}