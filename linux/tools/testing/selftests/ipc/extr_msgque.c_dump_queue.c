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
struct TYPE_3__ {int /*<<< orphan*/  mode; } ;
struct msqid_ds {int msg_qnum; int /*<<< orphan*/  msg_qbytes; TYPE_1__ msg_perm; } ;
struct msgque_data {int msq_id; int qnum; TYPE_2__* messages; int /*<<< orphan*/  qbytes; int /*<<< orphan*/  mode; } ;
struct msg1 {int dummy; } ;
struct TYPE_4__ {int msize; int /*<<< orphan*/  mtype; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int IPC_NOWAIT ; 
 int /*<<< orphan*/  MAX_MSG_SIZE ; 
 int MSG_COPY ; 
 int /*<<< orphan*/  MSG_STAT ; 
 int errno ; 
 TYPE_2__* malloc (int) ; 
 int msgctl (int,int /*<<< orphan*/ ,struct msqid_ds*) ; 
 int msgrcv (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int dump_queue(struct msgque_data *msgque)
{
	struct msqid_ds ds;
	int kern_id;
	int i, ret;

	for (kern_id = 0; kern_id < 256; kern_id++) {
		ret = msgctl(kern_id, MSG_STAT, &ds);
		if (ret < 0) {
			if (errno == -EINVAL)
				continue;
			printf("Failed to get stats for IPC queue with id %d\n",
					kern_id);
			return -errno;
		}

		if (ret == msgque->msq_id)
			break;
	}

	msgque->messages = malloc(sizeof(struct msg1) * ds.msg_qnum);
	if (msgque->messages == NULL) {
		printf("Failed to get stats for IPC queue\n");
		return -ENOMEM;
	}

	msgque->qnum = ds.msg_qnum;
	msgque->mode = ds.msg_perm.mode;
	msgque->qbytes = ds.msg_qbytes;

	for (i = 0; i < msgque->qnum; i++) {
		ret = msgrcv(msgque->msq_id, &msgque->messages[i].mtype,
				MAX_MSG_SIZE, i, IPC_NOWAIT | MSG_COPY);
		if (ret < 0) {
			printf("Failed to copy IPC message: %m (%d)\n", errno);
			return -errno;
		}
		msgque->messages[i].msize = ret;
	}
	return 0;
}