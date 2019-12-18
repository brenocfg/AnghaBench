#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_10__ {int /*<<< orphan*/  vt_context; int /*<<< orphan*/  addr_td; int /*<<< orphan*/  type_descriptors; } ;
struct TYPE_9__ {int /*<<< orphan*/ * col; int /*<<< orphan*/  valid; int /*<<< orphan*/  td; int /*<<< orphan*/  addr; } ;
typedef  TYPE_1__ RecoveryTypeDescriptor ;
typedef  int /*<<< orphan*/  RecoveryCompleteObjectLocator ;
typedef  TYPE_2__ RRTTIMSVCAnalContext ;

/* Variables and functions */
 TYPE_1__* ht_up_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ht_up_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  r_pvector_push (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* recovery_type_descriptor_new () ; 
 int /*<<< orphan*/  rtti_msvc_read_type_descriptor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

RecoveryTypeDescriptor *recovery_anal_type_descriptor(RRTTIMSVCAnalContext *context, ut64 addr, RecoveryCompleteObjectLocator *col) {
	RecoveryTypeDescriptor *td = ht_up_find (context->addr_td, addr, NULL);
	if (td) {
		if (col != NULL) {
			td->col = col;
		}
		return td;
	}

	td = recovery_type_descriptor_new ();
	if (!td) {
		return NULL;
	}
	r_pvector_push (&context->type_descriptors, td);
	ht_up_insert (context->addr_td, addr, td);
	td->addr = addr;
	td->valid = rtti_msvc_read_type_descriptor (context->vt_context, addr, &td->td);
	if (!td->valid) {
		return td;
	}

	td->col = col;

	return td;
}