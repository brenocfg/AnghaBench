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
 long atomic_long_read (int /*<<< orphan*/ *) ; 
 long nfs_access_max_cachesize ; 
 int /*<<< orphan*/  nfs_access_nr_entries ; 
 int /*<<< orphan*/  nfs_do_access_cache_scan (unsigned int) ; 

__attribute__((used)) static void
nfs_access_cache_enforce_limit(void)
{
	long nr_entries = atomic_long_read(&nfs_access_nr_entries);
	unsigned long diff;
	unsigned int nr_to_scan;

	if (nr_entries < 0 || nr_entries <= nfs_access_max_cachesize)
		return;
	nr_to_scan = 100;
	diff = nr_entries - nfs_access_max_cachesize;
	if (diff < nr_to_scan)
		nr_to_scan = diff;
	nfs_do_access_cache_scan(nr_to_scan);
}