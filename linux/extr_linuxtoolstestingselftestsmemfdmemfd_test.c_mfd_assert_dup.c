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
 int /*<<< orphan*/  abort () ; 
 int dup (int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int mfd_assert_dup(int fd)
{
	int r;

	r = dup(fd);
	if (r < 0) {
		printf("dup(%d) failed: %m\n", fd);
		abort();
	}

	return r;
}