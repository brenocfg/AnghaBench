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
struct thread {int fd; int /*<<< orphan*/ * buf; int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 scalar_t__ ENODEV ; 
 int /*<<< orphan*/  FUNCTIONFS_FIFO_FLUSH ; 
 int /*<<< orphan*/  FUNCTIONFS_FIFO_STATUS ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  err (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int ioctl (int,int /*<<< orphan*/ ) ; 
 struct thread* threads ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cleanup_thread(void *arg)
{
	struct thread *t = arg;
	int ret, fd;

	fd = t->fd;
	if (t->fd < 0)
		return;
	t->fd = -1;

	/* test the FIFO ioctls (non-ep0 code paths) */
	if (t != threads) {
		ret = ioctl(fd, FUNCTIONFS_FIFO_STATUS);
		if (ret < 0) {
			/* ENODEV reported after disconnect */
			if (errno != ENODEV)
				err("%s: get fifo status", t->filename);
		} else if (ret) {
			warn("%s: unclaimed = %d\n", t->filename, ret);
			if (ioctl(fd, FUNCTIONFS_FIFO_FLUSH) < 0)
				err("%s: fifo flush", t->filename);
		}
	}

	if (close(fd) < 0)
		err("%s: close", t->filename);

	free(t->buf);
	t->buf = NULL;
}