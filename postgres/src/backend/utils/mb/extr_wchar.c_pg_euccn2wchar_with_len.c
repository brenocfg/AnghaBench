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
typedef  int pg_wchar ;

/* Variables and functions */
 scalar_t__ IS_HIGHBIT_SET (unsigned char const) ; 
 unsigned char const SS2 ; 
 unsigned char const SS3 ; 

__attribute__((used)) static int
pg_euccn2wchar_with_len(const unsigned char *from, pg_wchar *to, int len)
{
	int			cnt = 0;

	while (len > 0 && *from)
	{
		if (*from == SS2 && len >= 3)	/* code set 2 (unused?) */
		{
			from++;
			*to = (SS2 << 16) | (*from++ << 8);
			*to |= *from++;
			len -= 3;
		}
		else if (*from == SS3 && len >= 3)	/* code set 3 (unused ?) */
		{
			from++;
			*to = (SS3 << 16) | (*from++ << 8);
			*to |= *from++;
			len -= 3;
		}
		else if (IS_HIGHBIT_SET(*from) && len >= 2) /* code set 1 */
		{
			*to = *from++ << 8;
			*to |= *from++;
			len -= 2;
		}
		else
		{
			*to = *from++;
			len--;
		}
		to++;
		cnt++;
	}
	*to = 0;
	return cnt;
}