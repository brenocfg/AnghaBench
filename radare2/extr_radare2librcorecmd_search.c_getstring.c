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
 scalar_t__ IS_PRINTABLE (char) ; 
 char* malloc (int) ; 

__attribute__((used)) static char *getstring(char *b, int l) {
	char *r, *res = malloc (l + 1);
	int i;
	if (!res) {
		return NULL;
	}
	for (i = 0, r = res; i < l; b++, i++) {
		if (IS_PRINTABLE (*b)) {
			*r++ = *b;
		}
	}
	*r = 0;
	return res;
}