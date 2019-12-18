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
 int /*<<< orphan*/  F_ADD_SEALS ; 
 int /*<<< orphan*/  F_GET_SEALS ; 
 int /*<<< orphan*/  abort () ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  printf (char*,int,unsigned int,unsigned int) ; 

__attribute__((used)) static void mfd_fail_add_seals(int fd, unsigned int seals)
{
	int r;
	unsigned int s;

	r = fcntl(fd, F_GET_SEALS);
	if (r < 0)
		s = 0;
	else
		s = (unsigned int)r;

	r = fcntl(fd, F_ADD_SEALS, seals);
	if (r >= 0) {
		printf("ADD_SEALS(%d, %u -> %u) didn't fail as expected\n",
				fd, s, seals);
		abort();
	}
}