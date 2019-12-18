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
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 char* strdup (char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void __appendString(const char *msg, char **s) {
	if (!s) {
		printf ("%s\n", msg);
	} else if (*s) {
		char *p = malloc (strlen (msg) + strlen (*s) + 1);
		if (p) {
			strcpy (p, *s);
			free (*s);
			*s = p;
			strcpy (p + strlen (p), msg);
		}
	} else {
		*s = strdup (msg);
	}
}