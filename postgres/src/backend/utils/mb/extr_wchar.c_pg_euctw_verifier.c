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
 int /*<<< orphan*/  IS_EUC_RANGE_VALID (unsigned char) ; 
 int /*<<< orphan*/  IS_HIGHBIT_SET (unsigned char) ; 
#define  SS2 129 
#define  SS3 128 

__attribute__((used)) static int
pg_euctw_verifier(const unsigned char *s, int len)
{
	int			l;
	unsigned char c1,
				c2;

	c1 = *s++;

	switch (c1)
	{
		case SS2:				/* CNS 11643 Plane 1-7 */
			l = 4;
			if (l > len)
				return -1;
			c2 = *s++;
			if (c2 < 0xa1 || c2 > 0xa7)
				return -1;
			c2 = *s++;
			if (!IS_EUC_RANGE_VALID(c2))
				return -1;
			c2 = *s++;
			if (!IS_EUC_RANGE_VALID(c2))
				return -1;
			break;

		case SS3:				/* unused */
			return -1;

		default:
			if (IS_HIGHBIT_SET(c1)) /* CNS 11643 Plane 1 */
			{
				l = 2;
				if (l > len)
					return -1;
				/* no further range check on c1? */
				c2 = *s++;
				if (!IS_EUC_RANGE_VALID(c2))
					return -1;
			}
			else
				/* must be ASCII */
			{
				l = 1;
			}
			break;
	}
	return l;
}