#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  grant_ref_t ;
struct TYPE_2__ {unsigned long (* end_foreign_transfer_ref ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__* gnttab_interface ; 
 unsigned long stub1 (int /*<<< orphan*/ ) ; 

unsigned long gnttab_end_foreign_transfer_ref(grant_ref_t ref)
{
	return gnttab_interface->end_foreign_transfer_ref(ref);
}