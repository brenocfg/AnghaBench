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
 int target_prefetch_pages ; 

__attribute__((used)) static void
assign_effective_io_concurrency(int newval, void *extra)
{
#ifdef USE_PREFETCH
	target_prefetch_pages = *((int *) extra);
#endif							/* USE_PREFETCH */
}