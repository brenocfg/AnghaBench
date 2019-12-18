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
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static char *getrange(char *s) {
	char *p = NULL;
	while (s && *s) {
		if (*s == ',') {
			p = s+1;
			*p=0;
		}
		if (*s == '[' || *s == ']') {
			memmove (s, s + 1, strlen (s + 1) + 1);
		}
		if (*s == '}') {
			*s = 0;
		}
		s++;
	}
	while (p && *p == ' ') {
		p++;
	}
	return p;
}