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
 size_t strlen (char const*) ; 

__attribute__((used)) static const char * r_cmd_java_consumetok (const char *str1, const char b, size_t len) {
	const char *p = str1;
	size_t i = 0;
	if (!p) {
		return p;
	}
	if (len == -1) {
		len = strlen (str1);
	}
	for ( ; i < len; i++,p++) {
		if (*p != b) {
			break;
		}
	}
	return p;
}