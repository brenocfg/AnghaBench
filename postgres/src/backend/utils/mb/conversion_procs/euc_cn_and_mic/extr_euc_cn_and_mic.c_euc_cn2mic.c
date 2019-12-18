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
 scalar_t__ IS_HIGHBIT_SET (unsigned char const) ; 
 int /*<<< orphan*/  LC_GB2312_80 ; 
 int /*<<< orphan*/  PG_EUC_CN ; 
 int /*<<< orphan*/  report_invalid_encoding (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void
euc_cn2mic(const unsigned char *euc, unsigned char *p, int len)
{
	int			c1;

	while (len > 0)
	{
		c1 = *euc;
		if (IS_HIGHBIT_SET(c1))
		{
			if (len < 2 || !IS_HIGHBIT_SET(euc[1]))
				report_invalid_encoding(PG_EUC_CN, (const char *) euc, len);
			*p++ = LC_GB2312_80;
			*p++ = c1;
			*p++ = euc[1];
			euc += 2;
			len -= 2;
		}
		else
		{						/* should be ASCII */
			if (c1 == 0)
				report_invalid_encoding(PG_EUC_CN, (const char *) euc, len);
			*p++ = c1;
			euc++;
			len--;
		}
	}
	*p = '\0';
}