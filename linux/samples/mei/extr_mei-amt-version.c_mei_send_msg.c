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
struct timeval {unsigned long tv_sec; unsigned long tv_usec; } ;
struct mei {scalar_t__ fd; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 scalar_t__ FD_ISSET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  mei_deinit (struct mei*) ; 
 int /*<<< orphan*/  mei_err (struct mei*,char*,...) ; 
 int /*<<< orphan*/  mei_msg (struct mei*,char*,...) ; 
 int /*<<< orphan*/  select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write (scalar_t__,unsigned char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t mei_send_msg(struct mei *me, const unsigned char *buffer,
			ssize_t len, unsigned long timeout)
{
	struct timeval tv;
	ssize_t written;
	ssize_t rc;
	fd_set set;

	tv.tv_sec = timeout / 1000;
	tv.tv_usec = (timeout % 1000) * 1000000;

	mei_msg(me, "call write length = %zd\n", len);

	written = write(me->fd, buffer, len);
	if (written < 0) {
		rc = -errno;
		mei_err(me, "write failed with status %zd %s\n",
			written, strerror(errno));
		goto out;
	}

	FD_ZERO(&set);
	FD_SET(me->fd, &set);
	rc = select(me->fd + 1 , &set, NULL, NULL, &tv);
	if (rc > 0 && FD_ISSET(me->fd, &set)) {
		mei_msg(me, "write success\n");
	} else if (rc == 0) {
		mei_err(me, "write failed on timeout with status\n");
		goto out;
	} else { /* rc < 0 */
		mei_err(me, "write failed on select with status %zd\n", rc);
		goto out;
	}

	rc = written;
out:
	if (rc < 0)
		mei_deinit(me);

	return rc;
}