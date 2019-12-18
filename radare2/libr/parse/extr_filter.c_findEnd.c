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
 scalar_t__ IS_HEXCHAR (char const) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static char *findEnd(const char *s) {
	while (*s == 'x' || IS_HEXCHAR (*s)) {
		s++;
		// also skip ansi escape codes here :?
	}
	return strdup (s);
}