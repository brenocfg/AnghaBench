#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int (* get_utype ) (TYPE_1__*,void**) ;int /*<<< orphan*/  (* get_print_type ) (TYPE_1__*,char**) ;} ;
struct TYPE_6__ {TYPE_1__ type_data; } ;
typedef  TYPE_1__ STypeInfo ;
typedef  TYPE_2__ SType ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  print_base_type (int,char**) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int stub1 (TYPE_1__*,void**) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,char**) ; 

__attribute__((used)) static void get_enum_print_type(void *type, char **name) {
	STypeInfo *ti = (STypeInfo *) type;
	SType *t = 0;
	char *tmp_name = 0;
	int name_len = 0;
	int need_to_free = 1;
	int base_type = 0;

	base_type = ti->get_utype (ti, (void **)&t);
	if (!t) {
		need_to_free = 0;
		print_base_type (base_type, &tmp_name);
	} else {
		ti = &t->type_data;
		ti->get_print_type (ti, &tmp_name);
	}

	name_len = strlen ("enum ");
	if (tmp_name) {
		name_len += strlen (tmp_name);
	}
	*name = (char *) malloc (name_len + 1);
	if (!(*name)) {
		if (need_to_free) {
			free (tmp_name);
		}
		return;
	}
	// name[name_len] = '\0';
	strcpy (*name, "enum ");
	if (tmp_name) {
		strcat (*name, tmp_name);
	}

	if (need_to_free) {
		free (tmp_name);
	}
}