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
 int NR_GRPINFO_CACHES ; 
 int /*<<< orphan*/ ** ext4_groupinfo_caches ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ext4_groupinfo_destroy_slabs(void)
{
	int i;

	for (i = 0; i < NR_GRPINFO_CACHES; i++) {
		kmem_cache_destroy(ext4_groupinfo_caches[i]);
		ext4_groupinfo_caches[i] = NULL;
	}
}