#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct submitter {unsigned int nr_files; int /*<<< orphan*/ * fds; int /*<<< orphan*/  ring_fd; TYPE_1__* files; } ;
typedef  int /*<<< orphan*/  __s32 ;
struct TYPE_2__ {unsigned int fixed_fd; int /*<<< orphan*/  real_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORING_REGISTER_FILES ; 
 int /*<<< orphan*/ * calloc (unsigned int,int) ; 
 scalar_t__ do_nop ; 
 int io_uring_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int io_uring_register_files(struct submitter *s)
{
	unsigned i;

	if (do_nop)
		return 0;

	s->fds = calloc(s->nr_files, sizeof(__s32));
	for (i = 0; i < s->nr_files; i++) {
		s->fds[i] = s->files[i].real_fd;
		s->files[i].fixed_fd = i;
	}

	return io_uring_register(s->ring_fd, IORING_REGISTER_FILES, s->fds,
					s->nr_files);
}