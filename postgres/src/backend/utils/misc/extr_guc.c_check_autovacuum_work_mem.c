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
typedef  int /*<<< orphan*/  GucSource ;

/* Variables and functions */

__attribute__((used)) static bool
check_autovacuum_work_mem(int *newval, void **extra, GucSource source)
{
	/*
	 * -1 indicates fallback.
	 *
	 * If we haven't yet changed the boot_val default of -1, just let it be.
	 * Autovacuum will look to maintenance_work_mem instead.
	 */
	if (*newval == -1)
		return true;

	/*
	 * We clamp manually-set values to at least 1MB.  Since
	 * maintenance_work_mem is always set to at least this value, do the same
	 * here.
	 */
	if (*newval < 1024)
		*newval = 1024;

	return true;
}