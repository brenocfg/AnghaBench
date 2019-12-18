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
compare_left(char const **a, char const *aend, char const **b, char const *bend)
{
     /* Compare two left-aligned numbers: the first to have a
        different value wins. */
	for(;; (*a)++, (*b)++) {
		if ((*a == aend || !isdigit((int)(unsigned char)**a)) &&
			(*b == bend || !isdigit((int)(unsigned char)**b)))
			return 0;
		else if (*a == aend || !isdigit((int)(unsigned char)**a))
			return -1;
		else if (*b == bend || !isdigit((int)(unsigned char)**b))
			return +1;
		 else if (**a < **b)
			 return -1;
		 else if (**a > **b)
			 return +1;
     }

     return 0;
}