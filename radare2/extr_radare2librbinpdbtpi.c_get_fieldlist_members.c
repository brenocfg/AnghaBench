#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * substructs; } ;
struct TYPE_3__ {scalar_t__ type_info; } ;
typedef  TYPE_1__ STypeInfo ;
typedef  TYPE_2__ SLF_FIELDLIST ;
typedef  int /*<<< orphan*/  RList ;

/* Variables and functions */

__attribute__((used)) static void get_fieldlist_members(void *type, RList **l) {
	STypeInfo *t = (STypeInfo *) type;
	SLF_FIELDLIST *lf_fieldlist = (SLF_FIELDLIST *) t->type_info;

	*l = lf_fieldlist->substructs;
}