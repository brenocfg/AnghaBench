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
struct TYPE_6__ {int /*<<< orphan*/  substructs; } ;
struct TYPE_5__ {struct TYPE_5__* type_info; int /*<<< orphan*/  (* free_ ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ STypeInfo ;
typedef  TYPE_2__ SLF_FIELDLIST ;
typedef  int /*<<< orphan*/  RListIter ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  r_list_free (int /*<<< orphan*/ ) ; 
 scalar_t__ r_list_iter_get (int /*<<< orphan*/ *) ; 
 scalar_t__ r_list_iter_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_list_iterator (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static void free_lf_fieldlist(void *type) {
	STypeInfo *t = (STypeInfo *) type;
	SLF_FIELDLIST *lf_fieldlist = (SLF_FIELDLIST *) t->type_info;
	RListIter *it;
	STypeInfo *type_info = 0;

	it = r_list_iterator(lf_fieldlist->substructs);
	while (r_list_iter_next(it)) {
		type_info = (STypeInfo *) r_list_iter_get(it);
		if (type_info->free_) {
			type_info->free_ (type_info);
		}
		if (type_info->type_info) {
			free(type_info->type_info);
		}
		free(type_info);
	}
	r_list_free (lf_fieldlist->substructs);
}