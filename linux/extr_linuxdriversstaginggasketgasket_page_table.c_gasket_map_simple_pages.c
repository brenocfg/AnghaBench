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
typedef  int /*<<< orphan*/  ulong ;
typedef  scalar_t__ uint ;
struct gasket_page_table {int /*<<< orphan*/  device; scalar_t__ base_slot; scalar_t__ entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int gasket_alloc_simple_entries (struct gasket_page_table*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gasket_page_table_unmap_nolock (struct gasket_page_table*,int /*<<< orphan*/ ,scalar_t__) ; 
 int gasket_perform_mapping (struct gasket_page_table*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ gasket_simple_page_idx (struct gasket_page_table*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gasket_map_simple_pages(struct gasket_page_table *pg_tbl,
				   ulong host_addr, ulong dev_addr,
				   uint num_pages)
{
	int ret;
	uint slot_idx = gasket_simple_page_idx(pg_tbl, dev_addr);

	ret = gasket_alloc_simple_entries(pg_tbl, dev_addr, num_pages);
	if (ret) {
		dev_err(pg_tbl->device,
			"page table slots %u (@ 0x%lx) to %u are not available\n",
			slot_idx, dev_addr, slot_idx + num_pages - 1);
		return ret;
	}

	ret = gasket_perform_mapping(pg_tbl, pg_tbl->entries + slot_idx,
				     pg_tbl->base_slot + slot_idx, host_addr,
				     num_pages, 1);

	if (ret) {
		gasket_page_table_unmap_nolock(pg_tbl, dev_addr, num_pages);
		dev_err(pg_tbl->device, "gasket_perform_mapping %d\n", ret);
	}
	return ret;
}