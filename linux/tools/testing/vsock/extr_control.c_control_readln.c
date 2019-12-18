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
 int /*<<< orphan*/  TIMEOUT ; 
 int /*<<< orphan*/  control_fd ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 char* realloc (char*,size_t) ; 
 int recv (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  timeout_begin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timeout_check (char*) ; 
 int /*<<< orphan*/  timeout_end () ; 

char *control_readln(void)
{
	char *buf = NULL;
	size_t idx = 0;
	size_t buflen = 0;

	timeout_begin(TIMEOUT);

	for (;;) {
		ssize_t ret;

		if (idx >= buflen) {
			char *new_buf;

			new_buf = realloc(buf, buflen + 80);
			if (!new_buf) {
				perror("realloc");
				exit(EXIT_FAILURE);
			}

			buf = new_buf;
			buflen += 80;
		}

		do {
			ret = recv(control_fd, &buf[idx], 1, 0);
			timeout_check("recv");
		} while (ret < 0 && errno == EINTR);

		if (ret == 0) {
			fprintf(stderr, "unexpected EOF on control socket\n");
			exit(EXIT_FAILURE);
		}

		if (ret != 1) {
			perror("recv");
			exit(EXIT_FAILURE);
		}

		if (buf[idx] == '\n') {
			buf[idx] = '\0';
			break;
		}

		idx++;
	}

	timeout_end();

	return buf;
}