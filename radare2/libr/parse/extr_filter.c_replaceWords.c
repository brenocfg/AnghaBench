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
 int /*<<< orphan*/  memmove (char*,char const*,int) ; 
 int strlen (char const*) ; 
 char* strstr (char*,char const*) ; 

__attribute__((used)) static void replaceWords(char *s, const char *k, const char *v) {
	for (;;) {
		char *p = strstr (s, k);
		if (!p) {
			break;
		}
		char *s = p + strlen (k);
		char *d = p + strlen (v);
		memmove (d, s, strlen (s) + 1);
		memmove (p, v, strlen (v));
		s = p + strlen (v);
	}
}