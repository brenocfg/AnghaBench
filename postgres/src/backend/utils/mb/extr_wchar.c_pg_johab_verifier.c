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
 int /*<<< orphan*/  IS_HIGHBIT_SET (unsigned char const) ; 
 int pg_johab_mblen (unsigned char const*) ; 

__attribute__((used)) static int
pg_johab_verifier(const unsigned char *s, int len)
{
	int			l,
				mbl;
	unsigned char c;

	l = mbl = pg_johab_mblen(s);

	if (len < l)
		return -1;

	if (!IS_HIGHBIT_SET(*s))
		return mbl;

	while (--l > 0)
	{
		c = *++s;
		if (!IS_EUC_RANGE_VALID(c))
			return -1;
	}
	return mbl;
}