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
struct io_uring_params {unsigned int flags; } ;
struct io_uring {int dummy; } ;
typedef  int /*<<< orphan*/  p ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int io_uring_queue_mmap (int,struct io_uring_params*,struct io_uring*) ; 
 int io_uring_setup (unsigned int,struct io_uring_params*) ; 
 int /*<<< orphan*/  memset (struct io_uring_params*,int /*<<< orphan*/ ,int) ; 

int io_uring_queue_init(unsigned entries, struct io_uring *ring, unsigned flags)
{
	struct io_uring_params p;
	int fd, ret;

	memset(&p, 0, sizeof(p));
	p.flags = flags;

	fd = io_uring_setup(entries, &p);
	if (fd < 0)
		return fd;

	ret = io_uring_queue_mmap(fd, &p, ring);
	if (ret)
		close(fd);

	return ret;
}