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
typedef  scalar_t__ __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 scalar_t__ mfd_assert_get_seals (int) ; 
 int /*<<< orphan*/  printf (char*,unsigned long long,unsigned long long,int) ; 

__attribute__((used)) static void mfd_assert_has_seals(int fd, __u64 seals)
{
	__u64 s;

	s = mfd_assert_get_seals(fd);
	if (s != seals) {
		printf("%llu != %llu = GET_SEALS(%d)\n",
		       (unsigned long long)seals, (unsigned long long)s, fd);
		abort();
	}
}