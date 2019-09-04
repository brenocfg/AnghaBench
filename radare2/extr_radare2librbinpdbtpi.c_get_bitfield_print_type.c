#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ length; } ;
struct TYPE_6__ {int (* get_base_type ) (TYPE_1__*,void**) ;int /*<<< orphan*/  (* get_print_type ) (TYPE_1__*,char**) ;scalar_t__ type_info; } ;
struct TYPE_7__ {TYPE_1__ type_data; } ;
typedef  TYPE_1__ STypeInfo ;
typedef  TYPE_2__ SType ;
typedef  TYPE_3__ SLF_BITFIELD ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  print_base_type (int,char**) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,...) ; 
 int strlen (char*) ; 
 int stub1 (TYPE_1__*,void**) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,char**) ; 

__attribute__((used)) static void get_bitfield_print_type(void *type, char **name) {
	STypeInfo *ti = (STypeInfo *) type;
	SType *t = 0;
	char *tmp_name = 0;
	int name_len = 0;
	int need_to_free = 1;
	int base_type = 0;
	SLF_BITFIELD *bitfeild_info = (SLF_BITFIELD *)ti->type_info;

	base_type = ti->get_base_type (ti, (void **)&t);
	if (!t) {
		need_to_free = 0;
		print_base_type (base_type, &tmp_name);
	} else {
		ti = &t->type_data;
		ti->get_print_type (ti, &tmp_name);
	}

	name_len = strlen ("bitfield ");
	if (tmp_name) {
		name_len += strlen (tmp_name);
	}
	name_len += 4;
	*name = (char *) malloc (name_len + 1 + 1);
	if (!(*name)) {
		if (need_to_free) {
			free (tmp_name);
		}
		return;
	}

	// name[name_len] = '\0';
	if (tmp_name) {
		sprintf (*name, "%s %s : %d", "bitfield", tmp_name, (int)bitfeild_info->length);
	} else {
		sprintf (*name, "%s : %d", "bitfield", (int)bitfeild_info->length);
	}

	if (need_to_free) {
		free (tmp_name);
	}
}