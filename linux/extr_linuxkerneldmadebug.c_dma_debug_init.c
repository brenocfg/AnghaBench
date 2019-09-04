#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int HASH_SIZE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ dma_debug_fs_init () ; 
 int dma_debug_initialized ; 
 TYPE_1__* dma_entry_hash ; 
 int global_disable ; 
 int /*<<< orphan*/  nr_prealloc_entries ; 
 int /*<<< orphan*/  nr_total_entries ; 
 int /*<<< orphan*/  num_free_entries ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 scalar_t__ prealloc_memory (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dma_debug_init(void)
{
	int i;

	/* Do not use dma_debug_initialized here, since we really want to be
	 * called to set dma_debug_initialized
	 */
	if (global_disable)
		return 0;

	for (i = 0; i < HASH_SIZE; ++i) {
		INIT_LIST_HEAD(&dma_entry_hash[i].list);
		spin_lock_init(&dma_entry_hash[i].lock);
	}

	if (dma_debug_fs_init() != 0) {
		pr_err("DMA-API: error creating debugfs entries - disabling\n");
		global_disable = true;

		return 0;
	}

	if (prealloc_memory(nr_prealloc_entries) != 0) {
		pr_err("DMA-API: debugging out of memory error - disabled\n");
		global_disable = true;

		return 0;
	}

	nr_total_entries = num_free_entries;

	dma_debug_initialized = true;

	pr_info("DMA-API: debugging enabled by kernel config\n");
	return 0;
}