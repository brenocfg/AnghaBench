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

__attribute__((used)) static inline char *str_purify_filename(char *dst, char *src, size_t size) /* {{{ */
{
	char *d, *end;

	d = dst;
	end = dst + size - 1;

	for (; d < end && *src; ++d, ++src) {
		if (* (unsigned char *) src < ' ' || * (unsigned char *) src > '\x7f') {
			*d = '.';
		} else {
			*d = *src;
		}
	}

	*d = '\0';

	return d;
}