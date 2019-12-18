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
struct TYPE_4__ {int /*<<< orphan*/ * ancestors; } ;
typedef  TYPE_1__ deparse_namespace ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/ * list_delete_first (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pop_child_plan(deparse_namespace *dpns, deparse_namespace *save_dpns)
{
	List	   *ancestors;

	/* Get rid of ancestors list cell added by push_child_plan */
	ancestors = list_delete_first(dpns->ancestors);

	/* Restore fields changed by push_child_plan */
	*dpns = *save_dpns;

	/* Make sure dpns->ancestors is right (may be unnecessary) */
	dpns->ancestors = ancestors;
}