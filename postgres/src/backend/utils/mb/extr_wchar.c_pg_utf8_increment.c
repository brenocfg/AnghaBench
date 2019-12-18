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

__attribute__((used)) static bool
pg_utf8_increment(unsigned char *charptr, int length)
{
	unsigned char a;
	unsigned char limit;

	switch (length)
	{
		default:
			/* reject lengths 5 and 6 for now */
			return false;
		case 4:
			a = charptr[3];
			if (a < 0xBF)
			{
				charptr[3]++;
				break;
			}
			/* FALL THRU */
		case 3:
			a = charptr[2];
			if (a < 0xBF)
			{
				charptr[2]++;
				break;
			}
			/* FALL THRU */
		case 2:
			a = charptr[1];
			switch (*charptr)
			{
				case 0xED:
					limit = 0x9F;
					break;
				case 0xF4:
					limit = 0x8F;
					break;
				default:
					limit = 0xBF;
					break;
			}
			if (a < limit)
			{
				charptr[1]++;
				break;
			}
			/* FALL THRU */
		case 1:
			a = *charptr;
			if (a == 0x7F || a == 0xDF || a == 0xEF || a == 0xF4)
				return false;
			charptr[0]++;
			break;
	}

	return true;
}