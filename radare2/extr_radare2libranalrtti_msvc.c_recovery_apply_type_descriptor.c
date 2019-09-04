#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  col_td_classes; TYPE_1__* vt_context; } ;
struct TYPE_10__ {int /*<<< orphan*/  name; } ;
struct TYPE_12__ {TYPE_3__* col; int /*<<< orphan*/  addr; TYPE_2__ td; int /*<<< orphan*/  valid; } ;
struct TYPE_11__ {int /*<<< orphan*/  base_td; int /*<<< orphan*/  vtable; int /*<<< orphan*/  valid; } ;
struct TYPE_9__ {int /*<<< orphan*/ * anal; } ;
typedef  TYPE_4__ RecoveryTypeDescriptor ;
typedef  TYPE_5__ RRTTIMSVCAnalContext ;
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*,int /*<<< orphan*/ ) ; 
 char* ht_up_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ht_up_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_anal_class_create (int /*<<< orphan*/ *,char*) ; 
 char* r_anal_rtti_msvc_demangle_class_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recovery_apply_bases (TYPE_5__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  recovery_apply_vtable (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 char* strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *recovery_apply_type_descriptor(RRTTIMSVCAnalContext *context, RecoveryTypeDescriptor *td) {
	if (!td->valid) {
		return NULL;
	}

	RAnal *anal = context->vt_context->anal;

	const char *existing = ht_up_find (context->col_td_classes, td->addr, NULL);
	if (existing != NULL) {
		return existing;
	}

	char *name = r_anal_rtti_msvc_demangle_class_name (td->td.name);
	if (!name) {
		eprintf("Failed to demangle a class name: \"%s\"\n", td->td.name);
		name = strdup (td->td.name);
		if (!name) {
			return NULL;
		}
	}

	r_anal_class_create (anal, name);
	ht_up_insert (context->col_td_classes, td->addr, name);

	if (!td->col || !td->col->valid) {
		return name;
	}

	recovery_apply_vtable (anal, name, td->col->vtable);
	recovery_apply_bases (context, name, &td->col->base_td);

	return name;
}