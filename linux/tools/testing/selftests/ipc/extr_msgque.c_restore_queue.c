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
struct msgque_data {int msq_id; int mode; int qnum; TYPE_1__* messages; int /*<<< orphan*/  key; } ;
struct TYPE_2__ {int /*<<< orphan*/  msize; int /*<<< orphan*/  mtype; } ;

/* Variables and functions */
 int EFAULT ; 
 int IPC_CREAT ; 
 int IPC_EXCL ; 
 int /*<<< orphan*/  IPC_NOWAIT ; 
 int /*<<< orphan*/  IPC_RMID ; 
 int /*<<< orphan*/  O_WRONLY ; 
 int errno ; 
 scalar_t__ msgctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int msgget (int /*<<< orphan*/ ,int) ; 
 scalar_t__ msgsnd (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int strlen (char*) ; 
 int write (int,char*,int) ; 

int restore_queue(struct msgque_data *msgque)
{
	int fd, ret, id, i;
	char buf[32];

	fd = open("/proc/sys/kernel/msg_next_id", O_WRONLY);
	if (fd == -1) {
		printf("Failed to open /proc/sys/kernel/msg_next_id\n");
		return -errno;
	}
	sprintf(buf, "%d", msgque->msq_id);

	ret = write(fd, buf, strlen(buf));
	if (ret != strlen(buf)) {
		printf("Failed to write to /proc/sys/kernel/msg_next_id\n");
		return -errno;
	}

	id = msgget(msgque->key, msgque->mode | IPC_CREAT | IPC_EXCL);
	if (id == -1) {
		printf("Failed to create queue\n");
		return -errno;
	}

	if (id != msgque->msq_id) {
		printf("Restored queue has wrong id (%d instead of %d)\n",
							id, msgque->msq_id);
		ret = -EFAULT;
		goto destroy;
	}

	for (i = 0; i < msgque->qnum; i++) {
		if (msgsnd(msgque->msq_id, &msgque->messages[i].mtype,
			   msgque->messages[i].msize, IPC_NOWAIT) != 0) {
			printf("msgsnd failed (%m)\n");
			ret = -errno;
			goto destroy;
		};
	}
	return 0;

destroy:
	if (msgctl(id, IPC_RMID, NULL))
		printf("Failed to destroy queue: %d\n", -errno);
	return ret;
}