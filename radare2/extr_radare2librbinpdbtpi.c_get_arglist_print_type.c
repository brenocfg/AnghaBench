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

__attribute__((used)) static void get_arglist_print_type(void *type, char **name) {
	(void) type;
	int name_len = 0;

	name_len = strlen ("arg_list");
	*name = (char *) malloc (name_len + 1);
	if (!(*name)) {
		return;
	}
	// name[name_len] = '\0';
	strcpy (*name, "arg_list");
//	STypeInfo *ti = (STypeInfo *) type;
//	SType *t = 0;
//	char *tmp_name = 0;
//	int name_len = 0;
//	int need_to_free = 1;
//	int base_type = 0;

//	base_type = ti->get_arg_type(ti, (void **)&t);
//	if (!t) {
//		need_to_free = 0;
//		print_base_type(base_type, &tmp_name);
//	} else {
//		ti = &t->type_data;
//		ti->get_print_type(ti, &tmp_name);
//	}

//	name_len = strlen("arglist ");
//	name_len += strlen(tmp_name);
//	*name = (char *) malloc(name_len + 1);
//	// name[name_len] = '\0';
//	strcpy(*name, "arglist ");
//	strcat(*name, tmp_name);

//	if (need_to_free)
//		free(tmp_name);
}