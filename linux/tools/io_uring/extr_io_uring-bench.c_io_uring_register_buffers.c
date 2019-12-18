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
struct submitter {int /*<<< orphan*/  iovecs; int /*<<< orphan*/  ring_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEPTH ; 
 int /*<<< orphan*/  IORING_REGISTER_BUFFERS ; 
 scalar_t__ do_nop ; 
 int io_uring_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int io_uring_register_buffers(struct submitter *s)
{
	if (do_nop)
		return 0;

	return io_uring_register(s->ring_fd, IORING_REGISTER_BUFFERS, s->iovecs,
					DEPTH);
}