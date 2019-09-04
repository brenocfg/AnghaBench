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
typedef  int /*<<< orphan*/  zend_uchar ;

/* Variables and functions */

__attribute__((used)) static void
php_mysqlnd_crypt(zend_uchar *buffer, const zend_uchar *s1, const zend_uchar *s2, size_t len)
{
	const zend_uchar *s1_end = s1 + len;
	while (s1 < s1_end) {
		*buffer++= *s1++ ^ *s2++;
	}
}