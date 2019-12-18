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
struct TYPE_2__ {int euc; int sjis; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_HIGHBIT_SET (int) ; 
 int PGSJISALTCODE ; 
 int /*<<< orphan*/  PG_EUC_JP ; 
 int SS2 ; 
 int SS3 ; 
 TYPE_1__* ibmkanji ; 
 int pg_encoding_verifymb (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  report_invalid_encoding (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void
euc_jp2sjis(const unsigned char *euc, unsigned char *p, int len)
{
	int			c1,
				c2,
				k;
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
		{
			/* hankaku kana? */
			*p++ = euc[1];
		}
		else if (c1 == SS3)
		{
			/* JIS X0212 kanji? */
			c1 = euc[1];
			c2 = euc[2];
			k = c1 << 8 | c2;
			if (k >= 0xf5a1)
			{
				/* UDC2 */
				c1 -= 0x54;
				*p++ = ((c1 - 0xa1) >> 1) + ((c1 < 0xdf) ? 0x81 : 0xc1) + 0x74;
				*p++ = c2 - ((c1 & 1) ? ((c2 < 0xe0) ? 0x61 : 0x60) : 2);
			}
			else
			{
				int			i,
							k2;

				/* IBM kanji */
				for (i = 0;; i++)
				{
					k2 = ibmkanji[i].euc & 0xffff;
					if (k2 == 0xffff)
					{
						*p++ = PGSJISALTCODE >> 8;
						*p++ = PGSJISALTCODE & 0xff;
						break;
					}
					if (k2 == k)
					{
						k = ibmkanji[i].sjis;
						*p++ = k >> 8;
						*p++ = k & 0xff;
						break;
					}
				}
			}
		}
		else
		{
			/* JIS X0208 kanji? */
			c2 = euc[1];
			k = (c1 << 8) | (c2 & 0xff);
			if (k >= 0xf5a1)
			{
				/* UDC1 */
				c1 -= 0x54;
				*p++ = ((c1 - 0xa1) >> 1) + ((c1 < 0xdf) ? 0x81 : 0xc1) + 0x6f;
			}
			else
				*p++ = ((c1 - 0xa1) >> 1) + ((c1 < 0xdf) ? 0x81 : 0xc1);
			*p++ = c2 - ((c1 & 1) ? ((c2 < 0xe0) ? 0x61 : 0x60) : 2);
		}
		euc += l;
		len -= l;
	}
	*p = '\0';
}