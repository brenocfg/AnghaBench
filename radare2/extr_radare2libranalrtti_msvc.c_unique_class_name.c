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
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ r_anal_class_exists (int /*<<< orphan*/ *,char const*) ; 
 char* r_str_newf (char*,char const*,int /*<<< orphan*/ ) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static char *unique_class_name(RAnal *anal, const char *original_name) {
	if (!r_anal_class_exists (anal, original_name)) {
		return strdup (original_name);
	}

	char *name = NULL;
	eprintf ("Warning: class name %s already taken!\n", original_name);
	int i = 1;

	do {
		free (name);
		name = r_str_newf ("%s.%d", original_name, i++);
		if (!name) {
			return NULL;
		}
	} while (r_anal_class_exists (anal, name));

	return name;
}