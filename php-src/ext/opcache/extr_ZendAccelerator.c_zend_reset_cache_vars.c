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
typedef  int /*<<< orphan*/  ZSMMG ;
typedef  int /*<<< orphan*/  ZCSG ;

/* Variables and functions */
 int /*<<< orphan*/  CG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_ptr_last ; 

__attribute__((used)) static void zend_reset_cache_vars(void)
{
	ZSMMG(memory_exhausted) = 0;
	ZCSG(hits) = 0;
	ZCSG(misses) = 0;
	ZCSG(blacklist_misses) = 0;
	ZSMMG(wasted_shared_memory) = 0;
	ZCSG(restart_pending) = 0;
	ZCSG(force_restart_time) = 0;
	ZCSG(map_ptr_last) = CG(map_ptr_last);
}