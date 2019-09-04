#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  spl_dual_it_object ;

/* Variables and functions */
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  spl_append_it_fetch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spl_dual_it_next (int /*<<< orphan*/ *,int) ; 
 scalar_t__ spl_dual_it_valid (int /*<<< orphan*/ *) ; 

void spl_append_it_next(spl_dual_it_object *intern) /* {{{ */
{
	if (spl_dual_it_valid(intern) == SUCCESS) {
		spl_dual_it_next(intern, 1);
	}
	spl_append_it_fetch(intern);
}