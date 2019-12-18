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
 unsigned int mfd_assert_get_seals (int) ; 
 int /*<<< orphan*/  printf (char*,unsigned int,unsigned int,int) ; 

__attribute__((used)) static void mfd_assert_has_seals(int fd, unsigned int seals)
{
	unsigned int s;

	s = mfd_assert_get_seals(fd);
	if (s != seals) {
		printf("%u != %u = GET_SEALS(%d)\n", seals, s, fd);
		abort();
	}
}