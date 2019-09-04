#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * substructs; } ;
struct TYPE_9__ {scalar_t__ field_list; } ;
struct TYPE_6__ {scalar_t__ type_info; } ;
struct TYPE_8__ {TYPE_1__ type_data; } ;
struct TYPE_7__ {scalar_t__ type_info; } ;
typedef  TYPE_2__ STypeInfo ;
typedef  TYPE_3__ SType ;
typedef  TYPE_4__ SLF_STRUCTURE ;
typedef  TYPE_5__ SLF_FIELDLIST ;
typedef  int /*<<< orphan*/  RList ;

/* Variables and functions */
 unsigned int base_idx ; 
 int /*<<< orphan*/  p_types_list ; 
 scalar_t__ r_list_get_n (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void get_struct_class_members(void *type, RList **l) {
	SLF_FIELDLIST *lf_fieldlist = 0;
	STypeInfo *t = (STypeInfo *) type;
	SLF_STRUCTURE *lf = (SLF_STRUCTURE *) t->type_info;
	unsigned int indx = 0;

	if (lf->field_list == 0) {
		*l = 0;
	} else {
		SType *tmp = 0;
		indx = lf->field_list - base_idx;
		tmp = (SType *)r_list_get_n(p_types_list, indx);
		lf_fieldlist = (SLF_FIELDLIST *) tmp->type_data.type_info;
		*l = lf_fieldlist->substructs;
	}
}