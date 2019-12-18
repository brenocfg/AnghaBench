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
struct uffd_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uffd ; 
 scalar_t__ uffd_handle_page_fault (struct uffd_msg*) ; 
 scalar_t__ uffd_read_msg (int /*<<< orphan*/ ,struct uffd_msg*) ; 
 int /*<<< orphan*/  uffd_read_mutex ; 

__attribute__((used)) static void *uffd_read_thread(void *arg)
{
	unsigned long *this_cpu_userfaults;
	struct uffd_msg msg;

	this_cpu_userfaults = (unsigned long *) arg;
	*this_cpu_userfaults = 0;

	pthread_mutex_unlock(&uffd_read_mutex);
	/* from here cancellation is ok */

	for (;;) {
		if (uffd_read_msg(uffd, &msg))
			continue;
		(*this_cpu_userfaults) += uffd_handle_page_fault(&msg);
	}
	return (void *)NULL;
}