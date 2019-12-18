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
 int /*<<< orphan*/  __appendString (char const*,void*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void __errorFunc(void *opaque, const char *msg) {
	__appendString (msg, opaque);
	char **p = (char **)opaque;
	if (p && *p) {
		int n = strlen(*p);
		char *ptr = malloc (n + 2);
		if (!ptr) {
			return;
		}
		strcpy (ptr, *p);
		ptr[n] = '\n';
		ptr[n + 1] = 0;
		free (*p);
		*p = ptr;
	}
}