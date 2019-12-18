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
 scalar_t__ memchr (char const*,char const,size_t) ; 
 scalar_t__ memcmp (char const*,char const*,size_t) ; 

__attribute__((used)) static const char *
lmemfind(const char *s1, size_t l1, const char *s2, size_t l2)
{
	const char *init;

	if (l2 == 0)
		return (s1); /* empty strings are everywhere */
	if (l2 > l1)
		return (NULL); /* avoids a negative 'l1' */
        /*
         * to search for a '*s2' inside 's1'
         * - 1st char will be checked by 'memchr'
         * - 's2' cannot be found after that
         */
        l2--;
        l1 = l1 - l2;
        while (l1 > 0 && (init = (const char *)memchr(s1, *s2, l1)) != NULL) {
                /* 1st char is already checked */
                init++;
                if (memcmp(init, s2 + 1, l2) == 0)
                        return init - 1;

                /* correct 'l1' and 's1' to try again */
                l1 -= (size_t)(init - s1);
                s1 = init;
        }
        /* not found */
        return (NULL);
}