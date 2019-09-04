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
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void get_vtshape_print_type(void *type, char **name) {
	int name_len = 0;

	name_len = strlen ("vtshape");
	*name = (char *) malloc (name_len + 1);
	if (!(*name)) {
		return;
	}
	// name[name_len] = '\0';
	strcpy (*name, "vthape");
}