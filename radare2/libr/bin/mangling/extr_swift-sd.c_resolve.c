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
struct Type {char* name; scalar_t__ code; } ;

/* Variables and functions */
 int strlen (scalar_t__) ; 
 int /*<<< orphan*/  strncmp (char const*,scalar_t__,int) ; 

__attribute__((used)) static const char *resolve(struct Type *t, const char *foo, const char **bar) {
	if (!t || !foo || !*foo) {
		return NULL;
	}
	for (; t[0].code; t++) {
		int len = strlen (t[0].code);
		if (!strncmp (foo, t[0].code, len)) {
			if (bar) {
				*bar = t[0].name;
			}
			return foo + len;
		}
	}
	return NULL;
}