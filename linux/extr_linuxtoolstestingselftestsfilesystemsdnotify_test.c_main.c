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
struct sigaction {int /*<<< orphan*/  sa_flags; int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_sigaction; } ;

/* Variables and functions */
 int DN_CREATE ; 
 int DN_MODIFY ; 
 int DN_MULTISHOT ; 
 int /*<<< orphan*/  F_NOTIFY ; 
 int /*<<< orphan*/  F_SETSIG ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  SA_SIGINFO ; 
 int SIGRTMIN ; 
 int event_fd ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  handler ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pause () ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  sigaction (int,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 

int main(void)
{
	struct sigaction act;
	int fd;

	act.sa_sigaction = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGRTMIN + 1, &act, NULL);

	fd = open(".", O_RDONLY);
	fcntl(fd, F_SETSIG, SIGRTMIN + 1);
	fcntl(fd, F_NOTIFY, DN_MODIFY|DN_CREATE|DN_MULTISHOT);
	/* we will now be notified if any of the files
	   in "." is modified or new files are created */
	while (1) {
		pause();
		printf("Got event on fd=%d\n", event_fd);
	}
}