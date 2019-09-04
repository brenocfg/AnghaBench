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

const char *snd_info_get_str(char *dest, const char *src, int len)
{
	int c;

	while (*src == ' ' || *src == '\t')
		src++;
	if (*src == '"' || *src == '\'') {
		c = *src++;
		while (--len > 0 && *src && *src != c) {
			*dest++ = *src++;
		}
		if (*src == c)
			src++;
	} else {
		while (--len > 0 && *src && *src != ' ' && *src != '\t') {
			*dest++ = *src++;
		}
	}
	*dest = 0;
	while (*src == ' ' || *src == '\t')
		src++;
	return src;
}