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
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  MSG_MORE ; 
 int /*<<< orphan*/  TIMEOUT ; 
 int /*<<< orphan*/  control_fd ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int send (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  timeout_begin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timeout_check (char*) ; 
 int /*<<< orphan*/  timeout_end () ; 

void control_writeln(const char *str)
{
	ssize_t len = strlen(str);
	ssize_t ret;

	timeout_begin(TIMEOUT);

	do {
		ret = send(control_fd, str, len, MSG_MORE);
		timeout_check("send");
	} while (ret < 0 && errno == EINTR);

	if (ret != len) {
		perror("send");
		exit(EXIT_FAILURE);
	}

	do {
		ret = send(control_fd, "\n", 1, 0);
		timeout_check("send");
	} while (ret < 0 && errno == EINTR);

	if (ret != 1) {
		perror("send");
		exit(EXIT_FAILURE);
	}

	timeout_end();
}