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
typedef  int zend_ulong ;
typedef  scalar_t__ zend_long ;

/* Variables and functions */

__attribute__((used)) static int php_filter_parse_octal(const char *str, size_t str_len, zend_long *ret) { /* {{{ */
	zend_ulong ctx_value = 0;
	const char *end = str + str_len;

	while (str < end) {
		if (*str >= '0' && *str <= '7') {
			zend_ulong n = ((*(str++)) - '0');

			if ((ctx_value > ((zend_ulong)(~(zend_long)0)) / 8) ||
				((ctx_value = ctx_value * 8) > ((zend_ulong)(~(zend_long)0)) - n)) {
				return -1;
			}
			ctx_value += n;
		} else {
			return -1;
		}
	}

	*ret = (zend_long)ctx_value;
	return 1;
}