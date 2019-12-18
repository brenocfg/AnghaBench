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
struct TYPE_3__ {int /*<<< orphan*/  (* get_name ) (TYPE_1__*,char**) ;} ;
typedef  TYPE_1__ STypeInfo ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char**) ; 

__attribute__((used)) static void get_enumerate_print_type(void *type, char **name) {
	STypeInfo *ti = (STypeInfo *) type;
	char *tmp_name = 0, *tmp1 = 0;
	int name_len = 0;

	ti->get_name (ti, &tmp_name);

	tmp1 = "enumerate ";
	name_len = strlen (tmp1);
	if (tmp_name) {
		name_len += strlen (tmp_name);
	}
	*name = (char *) malloc (name_len + 1);
	if (!(*name)) {
		return;
	}
	// name[name_len] = '\0';
	strcpy (*name, tmp1);
	if (tmp_name) {
		strcat (*name, tmp_name);
	}

	//	if (need_to_free)
	//		free(tmp_name);
}