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
 int /*<<< orphan*/  LC_JISX0201K ; 
 int /*<<< orphan*/  LC_JISX0208 ; 
 int /*<<< orphan*/  LC_JISX0212 ; 
 int /*<<< orphan*/  PG_EUC_JP ; 
 int SS2 ; 
 int SS3 ; 
 int pg_encoding_verifymb (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  report_invalid_encoding (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void
euc_jp2mic(const unsigned char *euc, unsigned char *p, int len)
{
	int			c1;
	int			l;

	while (len > 0)
	{
		c1 = *euc;
		if (!IS_HIGHBIT_SET(c1))
		{
			/* ASCII */
			if (c1 == 0)
				report_invalid_encoding(PG_EUC_JP,
										(const char *) euc, len);
			*p++ = c1;
			euc++;
			len--;
			continue;
		}
		l = pg_encoding_verifymb(PG_EUC_JP, (const char *) euc, len);
		if (l < 0)
			report_invalid_encoding(PG_EUC_JP,
									(const char *) euc, len);
		if (c1 == SS2)
		{						/* 1 byte kana? */
			*p++ = LC_JISX0201K;
			*p++ = euc[1];
		}
		else if (c1 == SS3)
		{						/* JIS X0212 kanji? */
			*p++ = LC_JISX0212;
			*p++ = euc[1];
			*p++ = euc[2];
		}
		else
		{						/* kanji? */
			*p++ = LC_JISX0208;
			*p++ = c1;
			*p++ = euc[1];
		}
		euc += l;
		len -= l;
	}
	*p = '\0';
}