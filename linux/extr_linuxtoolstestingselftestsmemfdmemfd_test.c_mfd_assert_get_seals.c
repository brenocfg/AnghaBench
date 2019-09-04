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

/* Variables and functions */
 int /*<<< orphan*/  F_GET_SEALS ; 
 int /*<<< orphan*/  abort () ; 
 int fcntl (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static unsigned int mfd_assert_get_seals(int fd)
{
	int r;

	r = fcntl(fd, F_GET_SEALS);
	if (r < 0) {
		printf("GET_SEALS(%d) failed: %m\n", fd);
		abort();
	}

	return (unsigned int)r;
}