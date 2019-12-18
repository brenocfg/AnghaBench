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
 scalar_t__ r_str_char_fullwidth (char const*,int) ; 

__attribute__((used)) static int __getUtf8Length(const char *s, int n) {
	int i = 0, j = 0, fullwidths = 0;
	while (s[i] && n > 0) {
		if ((s[i] & 0xc0) != 0x80) {
			j++;
			if (r_str_char_fullwidth (s + i, n)) {
				fullwidths++;
			}
		}
		n--;
		i++;
	}
	return j + fullwidths;
}