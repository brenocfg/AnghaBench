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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */

__attribute__((used)) static char *
sanitize_str(const char *s)
{
	static char buf[30 + 1];
	int			i;

	for (i = 0; i < sizeof(buf) - 1; i++)
	{
		char		c = s[i];

		if (c == '\0')
			break;

		if (c >= 0x21 && c <= 0x7E)
			buf[i] = c;
		else
			buf[i] = '?';
	}
	buf[i] = '\0';
	return buf;
}