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
struct TYPE_4__ {int /*<<< orphan*/  size; } ;
struct TYPE_3__ {scalar_t__ type_info; } ;
typedef  TYPE_1__ STypeInfo ;
typedef  TYPE_2__ SLF_ARRAY ;

/* Variables and functions */
 int /*<<< orphan*/  get_sval_val (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static void get_array_val(void *type, int *res) {
	STypeInfo *t = (STypeInfo *) type;
	SLF_ARRAY *lf_array = (SLF_ARRAY *) t->type_info;
	get_sval_val (&lf_array->size, res);
}