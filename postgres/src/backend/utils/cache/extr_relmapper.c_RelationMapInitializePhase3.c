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

/* Variables and functions */
 scalar_t__ IsBootstrapProcessingMode () ; 
 int /*<<< orphan*/  load_relmap_file (int) ; 

void
RelationMapInitializePhase3(void)
{
	/*
	 * In bootstrap mode, the map file isn't there yet, so do nothing.
	 */
	if (IsBootstrapProcessingMode())
		return;

	/*
	 * Load the local map file, die on error.
	 */
	load_relmap_file(false);
}