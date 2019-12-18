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
typedef  int ut8 ;

/* Variables and functions */
 scalar_t__ IS_PRINTABLE (char const) ; 

__attribute__((used)) static inline int __strnlen(const char *str, int len) {
	int l = 0;
	while (IS_PRINTABLE (*str) && --len) {
		if (((ut8)*str) == 0xff) {
			break;
		}
		str++;
		l++;
	}
	return l + 1;
}