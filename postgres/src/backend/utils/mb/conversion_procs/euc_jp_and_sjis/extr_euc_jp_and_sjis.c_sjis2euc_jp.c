#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int nec; int sjis; int euc; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_HIGHBIT_SET (int) ; 
 int PGEUCALTCODE ; 
 int /*<<< orphan*/  PG_SJIS ; 
 int /*<<< orphan*/  SS2 ; 
 void* SS3 ; 
 TYPE_1__* ibmkanji ; 
 int pg_encoding_verifymb (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  report_invalid_encoding (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void
sjis2euc_jp(const unsigned char *sjis, unsigned char *p, int len)
{
	int			c1,
				c2,
				i,
				k,
				k2;
	int			l;

	while (len > 0)
	{
		c1 = *sjis;
		if (!IS_HIGHBIT_SET(c1))
		{
			/* ASCII */
			if (c1 == 0)
				report_invalid_encoding(PG_SJIS,
										(const char *) sjis, len);
			*p++ = c1;
			sjis++;
			len--;
			continue;
		}
		l = pg_encoding_verifymb(PG_SJIS, (const char *) sjis, len);
		if (l < 0)
			report_invalid_encoding(PG_SJIS,
									(const char *) sjis, len);
		if (c1 >= 0xa1 && c1 <= 0xdf)
		{
			/* JIS X0201 (1 byte kana) */
			*p++ = SS2;
			*p++ = c1;
		}
		else
		{
			/*
			 * JIS X0208, X0212, user defined extended characters
			 */
			c2 = sjis[1];
			k = (c1 << 8) + c2;
			if (k >= 0xed40 && k < 0xf040)
			{
				/* NEC selection IBM kanji */
				for (i = 0;; i++)
				{
					k2 = ibmkanji[i].nec;
					if (k2 == 0xffff)
						break;
					if (k2 == k)
					{
						k = ibmkanji[i].sjis;
						c1 = (k >> 8) & 0xff;
						c2 = k & 0xff;
					}
				}
			}

			if (k < 0xeb3f)
			{
				/* JIS X0208 */
				*p++ = ((c1 & 0x3f) << 1) + 0x9f + (c2 > 0x9e);
				*p++ = c2 + ((c2 > 0x9e) ? 2 : 0x60) + (c2 < 0x80);
			}
			else if ((k >= 0xeb40 && k < 0xf040) || (k >= 0xfc4c && k <= 0xfcfc))
			{
				/* NEC selection IBM kanji - Other undecided justice */
				*p++ = PGEUCALTCODE >> 8;
				*p++ = PGEUCALTCODE & 0xff;
			}
			else if (k >= 0xf040 && k < 0xf540)
			{
				/*
				 * UDC1 mapping to X0208 85 ku - 94 ku JIS code 0x7521 -
				 * 0x7e7e EUC 0xf5a1 - 0xfefe
				 */
				c1 -= 0x6f;
				*p++ = ((c1 & 0x3f) << 1) + 0xf3 + (c2 > 0x9e);
				*p++ = c2 + ((c2 > 0x9e) ? 2 : 0x60) + (c2 < 0x80);
			}
			else if (k >= 0xf540 && k < 0xfa40)
			{
				/*
				 * UDC2 mapping to X0212 85 ku - 94 ku JIS code 0x7521 -
				 * 0x7e7e EUC 0x8ff5a1 - 0x8ffefe
				 */
				*p++ = SS3;
				c1 -= 0x74;
				*p++ = ((c1 & 0x3f) << 1) + 0xf3 + (c2 > 0x9e);
				*p++ = c2 + ((c2 > 0x9e) ? 2 : 0x60) + (c2 < 0x80);
			}
			else if (k >= 0xfa40)
			{
				/*
				 * mapping IBM kanji to X0208 and X0212
				 *
				 */
				for (i = 0;; i++)
				{
					k2 = ibmkanji[i].sjis;
					if (k2 == 0xffff)
						break;
					if (k2 == k)
					{
						k = ibmkanji[i].euc;
						if (k >= 0x8f0000)
						{
							*p++ = SS3;
							*p++ = 0x80 | ((k & 0xff00) >> 8);
							*p++ = 0x80 | (k & 0xff);
						}
						else
						{
							*p++ = 0x80 | (k >> 8);
							*p++ = 0x80 | (k & 0xff);
						}
					}
				}
			}
		}
		sjis += l;
		len -= l;
	}
	*p = '\0';
}