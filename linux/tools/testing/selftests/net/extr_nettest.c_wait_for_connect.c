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
typedef  int /*<<< orphan*/  val ;
struct timeval {scalar_t__ tv_sec; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SETSIZE ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_ERROR ; 
 scalar_t__ getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err_errno (char*) ; 
 int /*<<< orphan*/  log_error (char*,...) ; 
 scalar_t__ prog_timeout ; 
 int select (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  strerror (int) ; 

__attribute__((used)) static int wait_for_connect(int sd)
{
	struct timeval _tv = { .tv_sec = prog_timeout }, *tv = NULL;
	fd_set wfd;
	int val = 0, sz = sizeof(val);
	int rc;

	FD_ZERO(&wfd);
	FD_SET(sd, &wfd);

	if (prog_timeout)
		tv = &_tv;

	rc = select(FD_SETSIZE, NULL, &wfd, NULL, tv);
	if (rc == 0) {
		log_error("connect timed out\n");
		return -2;
	} else if (rc < 0) {
		log_err_errno("select failed");
		return -3;
	}

	if (getsockopt(sd, SOL_SOCKET, SO_ERROR, &val, (socklen_t *)&sz) < 0) {
		log_err_errno("getsockopt(SO_ERROR) failed");
		return -4;
	}

	if (val != 0) {
		log_error("connect failed: %d: %s\n", val, strerror(val));
		return -1;
	}

	return 0;
}