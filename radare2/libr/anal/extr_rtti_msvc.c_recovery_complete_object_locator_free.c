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
struct TYPE_4__ {int /*<<< orphan*/  base_td; int /*<<< orphan*/  bcd; } ;
typedef  TYPE_1__ RecoveryCompleteObjectLocator ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  r_list_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_vector_clear (int /*<<< orphan*/ *) ; 

void recovery_complete_object_locator_free(RecoveryCompleteObjectLocator *col) {
	if (!col) {
		return;
	}
	r_list_free (col->bcd);
	r_vector_clear (&col->base_td);
	free (col);
}