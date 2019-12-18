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
 int /*<<< orphan*/  IS_HIGHBIT_SET (unsigned char const) ; 

__attribute__((used)) static int
pg_gb18030_verifier(const unsigned char *s, int len)
{
	int			l;

	if (!IS_HIGHBIT_SET(*s))
		l = 1;					/* ASCII */
	else if (len >= 4 && *(s + 1) >= 0x30 && *(s + 1) <= 0x39)
	{
		/* Should be 4-byte, validate remaining bytes */
		if (*s >= 0x81 && *s <= 0xfe &&
			*(s + 2) >= 0x81 && *(s + 2) <= 0xfe &&
			*(s + 3) >= 0x30 && *(s + 3) <= 0x39)
			l = 4;
		else
			l = -1;
	}
	else if (len >= 2 && *s >= 0x81 && *s <= 0xfe)
	{
		/* Should be 2-byte, validate */
		if ((*(s + 1) >= 0x40 && *(s + 1) <= 0x7e) ||
			(*(s + 1) >= 0x80 && *(s + 1) <= 0xfe))
			l = 2;
		else
			l = -1;
	}
	else
		l = -1;
	return l;
}