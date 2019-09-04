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
struct mb_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mb_cache_destroy (struct mb_cache*) ; 

void ext4_xattr_destroy_cache(struct mb_cache *cache)
{
	if (cache)
		mb_cache_destroy(cache);
}