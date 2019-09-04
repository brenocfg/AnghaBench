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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int EOVERFLOW ; 
 int /*<<< orphan*/  div64_u64_rem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_div (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fls64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int scale64_check_overflow(u64 mult, u64 div, u64 *base)
{
	u64 tmp, rem;

	tmp = div64_u64_rem(*base, div, &rem);

	if (((int)sizeof(u64)*8 - fls64(mult) < fls64(tmp)) ||
	    ((int)sizeof(u64)*8 - fls64(mult) < fls64(rem)))
		return -EOVERFLOW;
	tmp *= mult;
	rem *= mult;

	do_div(rem, div);
	*base = tmp + rem;
	return 0;
}