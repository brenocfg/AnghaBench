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
 int /*<<< orphan*/  IS_HIGHBIT_SET (unsigned char) ; 
#define  SS2 129 
#define  SS3 128 

__attribute__((used)) static bool
pg_eucjp_increment(unsigned char *charptr, int length)
{
	unsigned char c1,
				c2;
	int			i;

	c1 = *charptr;

	switch (c1)
	{
		case SS2:				/* JIS X 0201 */
			if (length != 2)
				return false;

			c2 = charptr[1];

			if (c2 >= 0xdf)
				charptr[0] = charptr[1] = 0xa1;
			else if (c2 < 0xa1)
				charptr[1] = 0xa1;
			else
				charptr[1]++;
			break;

		case SS3:				/* JIS X 0212 */
			if (length != 3)
				return false;

			for (i = 2; i > 0; i--)
			{
				c2 = charptr[i];
				if (c2 < 0xa1)
				{
					charptr[i] = 0xa1;
					return true;
				}
				else if (c2 < 0xfe)
				{
					charptr[i]++;
					return true;
				}
			}

			/* Out of 3-byte code region */
			return false;

		default:
			if (IS_HIGHBIT_SET(c1)) /* JIS X 0208? */
			{
				if (length != 2)
					return false;

				for (i = 1; i >= 0; i--)
				{
					c2 = charptr[i];
					if (c2 < 0xa1)
					{
						charptr[i] = 0xa1;
						return true;
					}
					else if (c2 < 0xfe)
					{
						charptr[i]++;
						return true;
					}
				}

				/* Out of 2 byte code region */
				return false;
			}
			else
			{					/* ASCII, single byte */
				if (c1 > 0x7e)
					return false;
				(*charptr)++;
			}
			break;
	}

	return true;
}