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

int
significant_digits(const char *s)
{
	const char *p = s;
	int			n,
				c,
				zeroes;

	zeroes = 1;
	/* skip leading zeroes and sign */
	for (c = *p; (c == '0' || c == '+' || c == '-') && c != 0; c = *(++p));

	/* skip decimal point and following zeroes */
	for (c = *p; (c == '0' || c == '.') && c != 0; c = *(++p))
	{
		if (c != '.')
			zeroes++;
	}

	/* count significant digits (n) */
	for (c = *p, n = 0; c != 0; c = *(++p))
	{
		if (!((c >= '0' && c <= '9') || (c == '.')))
			break;
		if (c != '.')
			n++;
	}

	if (!n)
		return zeroes;

	return n;
}