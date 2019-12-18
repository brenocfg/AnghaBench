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
 int LC_JISX0201K ; 
 int LC_JISX0208 ; 
 int LC_JISX0212 ; 
 int PGSJISALTCODE ; 
 int /*<<< orphan*/  PG_MULE_INTERNAL ; 
 int /*<<< orphan*/  PG_SJIS ; 
 TYPE_1__* ibmkanji ; 
 int pg_encoding_verifymb (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  report_invalid_encoding (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  report_untranslatable_char (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void
mic2sjis(const unsigned char *mic, unsigned char *p, int len)
{
	int			c1,
				c2,
				k,
				l;

	while (len > 0)
	{
		c1 = *mic;
		if (!IS_HIGHBIT_SET(c1))
		{
			/* ASCII */
			if (c1 == 0)
				report_invalid_encoding(PG_MULE_INTERNAL,
										(const char *) mic, len);
			*p++ = c1;
			mic++;
			len--;
			continue;
		}
		l = pg_encoding_verifymb(PG_MULE_INTERNAL, (const char *) mic, len);
		if (l < 0)
			report_invalid_encoding(PG_MULE_INTERNAL,
									(const char *) mic, len);
		if (c1 == LC_JISX0201K)
			*p++ = mic[1];
		else if (c1 == LC_JISX0208)
		{
			c1 = mic[1];
			c2 = mic[2];
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
		else if (c1 == LC_JISX0212)
		{
			int			i,
						k2;

			c1 = mic[1];
			c2 = mic[2];
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
			report_untranslatable_char(PG_MULE_INTERNAL, PG_SJIS,
									   (const char *) mic, len);
		mic += l;
		len -= l;
	}
	*p = '\0';
}