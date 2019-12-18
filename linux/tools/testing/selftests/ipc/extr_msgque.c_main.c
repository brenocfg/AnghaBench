#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct msgque_data {int key; int msq_id; } ;

/* Variables and functions */
 int IPC_CREAT ; 
 int IPC_EXCL ; 
 int /*<<< orphan*/  IPC_RMID ; 
 int check_and_destroy_queue (struct msgque_data*) ; 
 int dump_queue (struct msgque_data*) ; 
 int errno ; 
 int fill_msgque (struct msgque_data*) ; 
 int ftok (char*,int) ; 
 scalar_t__ getuid () ; 
 int ksft_exit_fail () ; 
 int ksft_exit_pass () ; 
 int ksft_exit_skip (char*) ; 
 scalar_t__ msgctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int msgget (int,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int restore_queue (struct msgque_data*) ; 

int main(int argc, char **argv)
{
	int msg, pid, err;
	struct msgque_data msgque;

	if (getuid() != 0)
		return ksft_exit_skip(
				"Please run the test as root - Exiting.\n");

	msgque.key = ftok(argv[0], 822155650);
	if (msgque.key == -1) {
		printf("Can't make key: %d\n", -errno);
		return ksft_exit_fail();
	}

	msgque.msq_id = msgget(msgque.key, IPC_CREAT | IPC_EXCL | 0666);
	if (msgque.msq_id == -1) {
		err = -errno;
		printf("Can't create queue: %d\n", err);
		goto err_out;
	}

	err = fill_msgque(&msgque);
	if (err) {
		printf("Failed to fill queue: %d\n", err);
		goto err_destroy;
	}

	err = dump_queue(&msgque);
	if (err) {
		printf("Failed to dump queue: %d\n", err);
		goto err_destroy;
	}

	err = check_and_destroy_queue(&msgque);
	if (err) {
		printf("Failed to check and destroy queue: %d\n", err);
		goto err_out;
	}

	err = restore_queue(&msgque);
	if (err) {
		printf("Failed to restore queue: %d\n", err);
		goto err_destroy;
	}

	err = check_and_destroy_queue(&msgque);
	if (err) {
		printf("Failed to test queue: %d\n", err);
		goto err_out;
	}
	return ksft_exit_pass();

err_destroy:
	if (msgctl(msgque.msq_id, IPC_RMID, NULL)) {
		printf("Failed to destroy queue: %d\n", -errno);
		return ksft_exit_fail();
	}
err_out:
	return ksft_exit_fail();
}