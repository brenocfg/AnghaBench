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
struct shrink_control {int dummy; } ;

/* Variables and functions */
 unsigned long prune_cache_entries () ; 

__attribute__((used)) static unsigned long
nfsd_reply_cache_scan(struct shrinker *shrink, struct shrink_control *sc)
{
	return prune_cache_entries();
}