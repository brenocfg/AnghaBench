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
 int const INT_MAX ; 
 int const INT_MIN ; 

__attribute__((used)) static bool
increment_overflow(int *ip, int j)
{
	int const	i = *ip;

	/*----------
	 * If i >= 0 there can only be overflow if i + j > INT_MAX
	 * or if j > INT_MAX - i; given i >= 0, INT_MAX - i cannot overflow.
	 * If i < 0 there can only be overflow if i + j < INT_MIN
	 * or if j < INT_MIN - i; given i < 0, INT_MIN - i cannot overflow.
	 *----------
	 */
	if ((i >= 0) ? (j > INT_MAX - i) : (j < INT_MIN - i))
		return true;
	*ip += j;
	return false;
}