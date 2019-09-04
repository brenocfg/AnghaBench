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

__attribute__((used)) static int php_openssl_spki_cleanup(const char *src, char *dest)
{
	int removed = 0;

	while (*src) {
		if (*src != '\n' && *src != '\r') {
			*dest++ = *src;
		} else {
			++removed;
		}
		++src;
	}
	*dest = 0;
	return removed;
}