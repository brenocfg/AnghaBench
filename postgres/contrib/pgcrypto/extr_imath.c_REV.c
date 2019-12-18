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

__attribute__((used)) static inline void
REV(unsigned char *A, int N)
{
	unsigned char *u_ = A;
	unsigned char *v_ = u_ + N - 1;

	while (u_ < v_)
	{
		unsigned char xch = *u_;

		*u_++ = *v_;
		*v_-- = xch;
	}
}