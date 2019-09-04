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
typedef  int /*<<< orphan*/  ut64 ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_cons_printf (char*,char*,char const*) ; 
 int /*<<< orphan*/  sdb_atoi (char const*) ; 
 char* strchr (char*,char) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static int print_addrinfo (void *user, const char *k, const char *v) {
	char *colonpos, *subst;

	ut64 offset = sdb_atoi (k);
	if (!offset) {
		return true;
	}
	subst = strdup (v);
	colonpos = strchr (subst, '|');

	if (colonpos) {
		*colonpos = ':';
	}
	r_cons_printf ("CL %s %s\n", subst, k);
	free (subst);

	return true;
}