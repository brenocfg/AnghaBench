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
struct bpf_link_fd {int /*<<< orphan*/  fd; } ;
struct bpf_link {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_EVENT_IOC_DISABLE ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int errno ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bpf_link__destroy_perf_event(struct bpf_link *link)
{
	struct bpf_link_fd *l = (void *)link;
	int err;

	err = ioctl(l->fd, PERF_EVENT_IOC_DISABLE, 0);
	if (err)
		err = -errno;

	close(l->fd);
	return err;
}