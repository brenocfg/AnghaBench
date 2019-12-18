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

/* Variables and functions */
 int /*<<< orphan*/  FD_CLOEXEC ; 
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  O_CLOEXEC ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int pipe (int*) ; 
 int pipe2 (int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void initpipe(int* fds) {
	int retval;

#ifdef HAVE_PIPE2
	retval = pipe2(fds, O_CLOEXEC);
#else
	retval = pipe(fds);
	if(retval == 0) {
		fcntl(fds[0], F_SETFD, FD_CLOEXEC);
		fcntl(fds[1], F_SETFD, FD_CLOEXEC);
	}
#endif
	if(retval == -1) {
		perror("pipe");
		exit(1);
	}
}