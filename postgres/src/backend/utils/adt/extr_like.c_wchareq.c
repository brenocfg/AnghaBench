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
 int pg_mblen (char const*) ; 

__attribute__((used)) static inline int
wchareq(const char *p1, const char *p2)
{
	int			p1_len;

	/* Optimization:  quickly compare the first byte. */
	if (*p1 != *p2)
		return 0;

	p1_len = pg_mblen(p1);
	if (pg_mblen(p2) != p1_len)
		return 0;

	/* They are the same length */
	while (p1_len--)
	{
		if (*p1++ != *p2++)
			return 0;
	}
	return 1;
}