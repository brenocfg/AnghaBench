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
struct shrinker {int dummy; } ;
struct shrink_control {int nr_to_scan; int gfp_mask; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int GFP_KERNEL ; 
 unsigned long SHRINK_STOP ; 
 unsigned long nfs_do_access_cache_scan (int) ; 

unsigned long
nfs_access_cache_scan(struct shrinker *shrink, struct shrink_control *sc)
{
	int nr_to_scan = sc->nr_to_scan;
	gfp_t gfp_mask = sc->gfp_mask;

	if ((gfp_mask & GFP_KERNEL) != GFP_KERNEL)
		return SHRINK_STOP;
	return nfs_do_access_cache_scan(nr_to_scan);
}