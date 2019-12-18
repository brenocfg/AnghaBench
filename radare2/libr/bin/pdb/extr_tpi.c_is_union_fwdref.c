#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int fwdref; } ;
struct TYPE_6__ {TYPE_1__ bits; } ;
struct TYPE_8__ {TYPE_2__ prop; } ;
struct TYPE_7__ {scalar_t__ type_info; } ;
typedef  TYPE_3__ STypeInfo ;
typedef  TYPE_4__ SLF_UNION ;

/* Variables and functions */

__attribute__((used)) static void is_union_fwdref(void *type, int *is_fwdref) {
	STypeInfo *t = (STypeInfo *) type;
	SLF_UNION *lf = (SLF_UNION *) t->type_info;

	*is_fwdref = lf->prop.bits.fwdref;
}