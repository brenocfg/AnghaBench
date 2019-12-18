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
typedef  scalar_t__ ut64 ;

/* Variables and functions */
 scalar_t__ UT64_MAX ; 
 int /*<<< orphan*/  filter_count ; 
 scalar_t__ filter_format ; 
 scalar_t__ filter_offset ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_cons_printf (char*,char const*,...) ; 
 scalar_t__ sdb_atoi (char const*) ; 
 char* strchr (char*,char) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static int print_addrinfo (void *user, const char *k, const char *v) {
	ut64 offset = sdb_atoi (k);
	if (!offset || offset == UT64_MAX) {
		return true;
	}
	char *subst = strdup (v);
	char *colonpos = strchr (subst, '|'); // XXX keep only : for simplicity?
	if (!colonpos) {
		colonpos = strchr (subst, ':');
	}
	if (!colonpos) {
		r_cons_printf ("%s\n", subst);
	}
	if (colonpos && (filter_offset == UT64_MAX || filter_offset == offset)) {
		if (filter_format) {
			*colonpos = ':';
			r_cons_printf ("CL %s %s\n", k, subst);
		} else {
			*colonpos = 0;
			r_cons_printf ("file: %s\nline: %s\n", subst, colonpos + 1);
		}
		filter_count++;
	}
	free (subst);

	return true;
}