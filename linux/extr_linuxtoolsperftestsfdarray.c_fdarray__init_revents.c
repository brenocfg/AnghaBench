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
struct fdarray {int nr; int nr_alloc; TYPE_1__* entries; } ;
struct TYPE_2__ {int fd; short revents; } ;

/* Variables and functions */

__attribute__((used)) static void fdarray__init_revents(struct fdarray *fda, short revents)
{
	int fd;

	fda->nr = fda->nr_alloc;

	for (fd = 0; fd < fda->nr; ++fd) {
		fda->entries[fd].fd	 = fda->nr - fd;
		fda->entries[fd].revents = revents;
	}
}