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
 char lastChar (char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,int) ; 
 int strstr (char const*,char const*) ; 

__attribute__((used)) static bool match(const char *str, const char *expr) {
	bool startsWith = *expr == '^';
	bool endsWith = lastChar (expr) == '$';
	if (startsWith && endsWith) {
		return strlen (str) == strlen (expr) - 2 && \
			!strncmp (str, expr + 1, strlen (expr) - 2);
	}
	if (startsWith) {
		return !strncmp (str, expr + 1, strlen (expr) - 1);
	}
	if (endsWith) {
		int alen = strlen (str);
		int blen = strlen (expr) - 1;
		if (alen <= blen) {
			return false;
		}
		const char *a = str + strlen (str) - blen;
		return (!strncmp (a, expr, blen));
	}
	return strstr (str, expr);
}