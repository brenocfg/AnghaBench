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
 int /*<<< orphan*/  IS_HIGHBIT_SET (int) ; 
 int /*<<< orphan*/  PG_SHIFT_JIS_2004 ; 
 int /*<<< orphan*/  SS2 ; 
 int /*<<< orphan*/  SS3 ; 
 int get_ten (int,int*) ; 
 int pg_encoding_verifymb (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  report_invalid_encoding (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void
shift_jis_20042euc_jis_2004(const unsigned char *sjis, unsigned char *p, int len)
{
	int			c1;
	int			ku,
				ten,
				kubun;
	int			plane;
	int			l;

	while (len > 0)
	{
		c1 = *sjis;

		if (!IS_HIGHBIT_SET(c1))
		{
			/* ASCII */
			if (c1 == 0)
				report_invalid_encoding(PG_SHIFT_JIS_2004,
										(const char *) sjis, len);
			*p++ = c1;
			sjis++;
			len--;
			continue;
		}

		l = pg_encoding_verifymb(PG_SHIFT_JIS_2004, (const char *) sjis, len);

		if (l < 0 || l > len)
			report_invalid_encoding(PG_SHIFT_JIS_2004,
									(const char *) sjis, len);

		if (c1 >= 0xa1 && c1 <= 0xdf && l == 1)
		{
			/* JIS X0201 (1 byte kana) */
			*p++ = SS2;
			*p++ = c1;
		}
		else if (l == 2)
		{
			int			c2 = sjis[1];

			plane = 1;
			ku = 1;
			ten = 1;

			/*
			 * JIS X 0213
			 */
			if (c1 >= 0x81 && c1 <= 0x9f)	/* plane 1 1ku-62ku */
			{
				ku = (c1 << 1) - 0x100;
				ten = get_ten(c2, &kubun);
				if (ten < 0)
					report_invalid_encoding(PG_SHIFT_JIS_2004,
											(const char *) sjis, len);
				ku -= kubun;
			}
			else if (c1 >= 0xe0 && c1 <= 0xef)	/* plane 1 62ku-94ku */
			{
				ku = (c1 << 1) - 0x180;
				ten = get_ten(c2, &kubun);
				if (ten < 0)
					report_invalid_encoding(PG_SHIFT_JIS_2004,

											(const char *) sjis, len);
				ku -= kubun;
			}
			else if (c1 >= 0xf0 && c1 <= 0xf3)	/* plane 2
												 * 1,3,4,5,8,12,13,14,15 ku */
			{
				plane = 2;
				ten = get_ten(c2, &kubun);
				if (ten < 0)
					report_invalid_encoding(PG_SHIFT_JIS_2004,
											(const char *) sjis, len);
				switch (c1)
				{
					case 0xf0:
						ku = kubun == 0 ? 8 : 1;
						break;
					case 0xf1:
						ku = kubun == 0 ? 4 : 3;
						break;
					case 0xf2:
						ku = kubun == 0 ? 12 : 5;
						break;
					default:
						ku = kubun == 0 ? 14 : 13;
						break;
				}
			}
			else if (c1 >= 0xf4 && c1 <= 0xfc)	/* plane 2 78-94ku */
			{
				plane = 2;
				ten = get_ten(c2, &kubun);
				if (ten < 0)
					report_invalid_encoding(PG_SHIFT_JIS_2004,
											(const char *) sjis, len);
				if (c1 == 0xf4 && kubun == 1)
					ku = 15;
				else
					ku = (c1 << 1) - 0x19a - kubun;
			}
			else
				report_invalid_encoding(PG_SHIFT_JIS_2004,
										(const char *) sjis, len);

			if (plane == 2)
				*p++ = SS3;

			*p++ = ku + 0xa0;
			*p++ = ten + 0xa0;
		}
		sjis += l;
		len -= l;
	}
	*p = '\0';
}