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
 int DIV_ROUND_UP (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_DEBUG_DYNAMIC_ENTRIES ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HASH_SIZE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_debug_create_entries (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_debug_fs_init () ; 
 int dma_debug_initialized ; 
 TYPE_1__* dma_entry_hash ; 
 int global_disable ; 
 scalar_t__ min_free_entries ; 
 scalar_t__ nr_prealloc_entries ; 
 int /*<<< orphan*/  nr_total_entries ; 
 scalar_t__ num_free_entries ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  pr_warn (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dma_debug_init(void)
{
	int i, nr_pages;

	/* Do not use dma_debug_initialized here, since we really want to be
	 * called to set dma_debug_initialized
	 */
	if (global_disable)
		return 0;

	for (i = 0; i < HASH_SIZE; ++i) {
		INIT_LIST_HEAD(&dma_entry_hash[i].list);
		spin_lock_init(&dma_entry_hash[i].lock);
	}

	dma_debug_fs_init();

	nr_pages = DIV_ROUND_UP(nr_prealloc_entries, DMA_DEBUG_DYNAMIC_ENTRIES);
	for (i = 0; i < nr_pages; ++i)
		dma_debug_create_entries(GFP_KERNEL);
	if (num_free_entries >= nr_prealloc_entries) {
		pr_info("preallocated %d debug entries\n", nr_total_entries);
	} else if (num_free_entries > 0) {
		pr_warn("%d debug entries requested but only %d allocated\n",
			nr_prealloc_entries, nr_total_entries);
	} else {
		pr_err("debugging out of memory error - disabled\n");
		global_disable = true;

		return 0;
	}
	min_free_entries = num_free_entries;

	dma_debug_initialized = true;

	pr_info("debugging enabled by kernel config\n");
	return 0;
}