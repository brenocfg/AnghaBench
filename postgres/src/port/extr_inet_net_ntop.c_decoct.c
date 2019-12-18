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
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int /*<<< orphan*/  SPRINTF (char*) ; 

__attribute__((used)) static int
decoct(const u_char *src, int bytes, char *dst, size_t size)
{
	char	   *odst = dst;
	char	   *t;
	int			b;

	for (b = 1; b <= bytes; b++)
	{
		if (size <= sizeof "255.")
			return (0);
		t = dst;
		dst += SPRINTF((dst, "%u", *src++));
		if (b != bytes)
		{
			*dst++ = '.';
			*dst = '\0';
		}
		size -= (size_t) (dst - t);
	}
	return (dst - odst);
}