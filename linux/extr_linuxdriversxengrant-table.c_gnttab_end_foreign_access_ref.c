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
typedef  int /*<<< orphan*/  grant_ref_t ;

/* Variables and functions */
 scalar_t__ _gnttab_end_foreign_access_ref (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 

int gnttab_end_foreign_access_ref(grant_ref_t ref, int readonly)
{
	if (_gnttab_end_foreign_access_ref(ref, readonly))
		return 1;
	pr_warn("WARNING: g.e. %#x still in use!\n", ref);
	return 0;
}