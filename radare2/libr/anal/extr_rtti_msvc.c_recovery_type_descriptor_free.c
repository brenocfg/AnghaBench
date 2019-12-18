#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  td; } ;
typedef  TYPE_1__ RecoveryTypeDescriptor ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  rtti_type_descriptor_fini (int /*<<< orphan*/ *) ; 

void recovery_type_descriptor_free(RecoveryTypeDescriptor *td) {
	if (!td) {
		return;
	}
	rtti_type_descriptor_fini (&td->td);
	free (td);
}