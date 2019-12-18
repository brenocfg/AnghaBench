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
 int JBD2_MAX_SLABS ; 
 int /*<<< orphan*/ ** jbd2_slab ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void jbd2_journal_destroy_slabs(void)
{
	int i;

	for (i = 0; i < JBD2_MAX_SLABS; i++) {
		kmem_cache_destroy(jbd2_slab[i]);
		jbd2_slab[i] = NULL;
	}
}