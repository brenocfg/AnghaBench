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
 int /*<<< orphan*/  isdigit (int) ; 

__attribute__((used)) static int
compare_right(char const **a, char const *aend, char const **b, char const *bend)
{
	int bias = 0;

	/* The longest run of digits wins.  That aside, the greatest
	   value wins, but we can't know that it will until we've scanned
	   both numbers to know that they have the same magnitude, so we
	   remember it in BIAS. */
	for(;; (*a)++, (*b)++) {
		if ((*a == aend || !isdigit((int)(unsigned char)**a)) &&
			(*b == bend || !isdigit((int)(unsigned char)**b)))
			return bias;
		else if (*a == aend || !isdigit((int)(unsigned char)**a))
			return -1;
		else if (*b == bend || !isdigit((int)(unsigned char)**b))
			return +1;
		else if (**a < **b) {
			if (!bias)
				bias = -1;
		} else if (**a > **b) {
			if (!bias)
				bias = +1;
		}
     }

     return 0;
}