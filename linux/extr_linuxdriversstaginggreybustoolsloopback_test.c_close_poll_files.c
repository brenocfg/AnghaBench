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
struct loopback_test {int poll_count; TYPE_1__* fds; } ;
struct TYPE_2__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int close_poll_files(struct loopback_test *t)
{
	int i;
	for (i = 0; i < t->poll_count; i++)
		close(t->fds[i].fd);

	return 0;
}