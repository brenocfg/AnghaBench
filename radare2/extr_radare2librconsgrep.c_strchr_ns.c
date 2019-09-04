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
 int /*<<< orphan*/  memmove (char*,char*,scalar_t__) ; 
 char* strchr (char*,char const) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static char *strchr_ns (char *s, const char ch) {
	char *p = strchr (s, ch);
	if (p && p > s) {
		char *prev = p - 1;
		if (*prev == '\\') {
			memmove (prev, p, strlen (p) + 1);
			return strchr_ns (p, ch);
		}
	}
	return p;
}