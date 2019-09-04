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
struct TYPE_2__ {int (* query_foreign_access ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__* gnttab_interface ; 
 int stub1 (int /*<<< orphan*/ ) ; 

int gnttab_query_foreign_access(grant_ref_t ref)
{
	return gnttab_interface->query_foreign_access(ref);
}