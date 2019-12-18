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
struct io_uring_params {int dummy; } ;
struct io_uring {int ring_fd; int /*<<< orphan*/  cq; int /*<<< orphan*/  sq; } ;

/* Variables and functions */
 int io_uring_mmap (int,struct io_uring_params*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct io_uring*,int /*<<< orphan*/ ,int) ; 

int io_uring_queue_mmap(int fd, struct io_uring_params *p, struct io_uring *ring)
{
	int ret;

	memset(ring, 0, sizeof(*ring));
	ret = io_uring_mmap(fd, p, &ring->sq, &ring->cq);
	if (!ret)
		ring->ring_fd = fd;
	return ret;
}