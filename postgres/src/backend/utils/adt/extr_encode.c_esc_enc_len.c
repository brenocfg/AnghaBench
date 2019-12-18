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
 scalar_t__ IS_HIGHBIT_SET (char const) ; 

__attribute__((used)) static unsigned
esc_enc_len(const char *src, unsigned srclen)
{
	const char *end = src + srclen;
	int			len = 0;

	while (src < end)
	{
		if (*src == '\0' || IS_HIGHBIT_SET(*src))
			len += 4;
		else if (*src == '\\')
			len += 2;
		else
			len++;

		src++;
	}

	return len;
}