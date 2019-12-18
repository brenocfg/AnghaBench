#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ leaf_type; int /*<<< orphan*/  (* get_name ) (TYPE_1__*,char**) ;} ;
typedef  TYPE_1__ STypeInfo ;
typedef  scalar_t__ ELeafType ;

/* Variables and functions */
 scalar_t__ eLF_CLASS ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char**) ; 

__attribute__((used)) static void get_class_struct_print_type(void *type, char **name) {
	STypeInfo *ti = (STypeInfo *) type;
	ELeafType lt;
	char *tmp_name = 0, *tmp1 = 0;
	int name_len = 0;

	lt = ti->leaf_type;
	ti->get_name(ti, &tmp_name);

	if (lt == eLF_CLASS) {
		tmp1 = "class ";
	} else {
		tmp1 = "struct ";
	}
	name_len = strlen(tmp1);
	if (tmp_name) {
		name_len += strlen (tmp_name);
	}
	*name = (char *) malloc(name_len + 1);
	if (!(*name)) {
		return;
	}
	// name[name_len] = '\0';
	strcpy(*name, tmp1);
	if (tmp_name) {
		strcat (*name, tmp_name);
	}

	//	if (need_to_free) {
	//		free(tmp_name);
	//		tmp_name = 0;
	//	}
}