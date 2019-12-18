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
typedef  int /*<<< orphan*/  uint8 ;

/* Variables and functions */
 int PXE_PGP_CORRUPT_ARMOR ; 

__attribute__((used)) static int
pg_base64_decode(const uint8 *src, unsigned len, uint8 *dst)
{
	const uint8 *srcend = src + len,
			   *s = src;
	uint8	   *p = dst;
	char		c;
	unsigned	b = 0;
	unsigned long buf = 0;
	int			pos = 0,
				end = 0;

	while (s < srcend)
	{
		c = *s++;
		if (c >= 'A' && c <= 'Z')
			b = c - 'A';
		else if (c >= 'a' && c <= 'z')
			b = c - 'a' + 26;
		else if (c >= '0' && c <= '9')
			b = c - '0' + 52;
		else if (c == '+')
			b = 62;
		else if (c == '/')
			b = 63;
		else if (c == '=')
		{
			/*
			 * end sequence
			 */
			if (!end)
			{
				if (pos == 2)
					end = 1;
				else if (pos == 3)
					end = 2;
				else
					return PXE_PGP_CORRUPT_ARMOR;
			}
			b = 0;
		}
		else if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
			continue;
		else
			return PXE_PGP_CORRUPT_ARMOR;

		/*
		 * add it to buffer
		 */
		buf = (buf << 6) + b;
		pos++;
		if (pos == 4)
		{
			*p++ = (buf >> 16) & 255;
			if (end == 0 || end > 1)
				*p++ = (buf >> 8) & 255;
			if (end == 0 || end > 2)
				*p++ = buf & 255;
			buf = 0;
			pos = 0;
		}
	}

	if (pos != 0)
		return PXE_PGP_CORRUPT_ARMOR;
	return p - dst;
}