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
typedef  scalar_t__ pg_wchar ;

/* Variables and functions */

__attribute__((used)) static int
pg_wcscmp(const pg_wchar *s1, const pg_wchar *s2)
{
	for (;;)
	{
		if (*s1 < *s2)
			return -1;
		if (*s1 > *s2)
			return 1;
		if (*s1 == 0)
			return 0;
		s1++;
		s2++;
	}
}