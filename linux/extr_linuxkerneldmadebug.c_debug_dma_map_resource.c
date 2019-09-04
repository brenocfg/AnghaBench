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
struct dma_debug_entry {size_t size; int direction; int /*<<< orphan*/  map_err_type; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  offset; int /*<<< orphan*/  pfn; struct device* dev; int /*<<< orphan*/  type; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAP_ERR_NOT_CHECKED ; 
 int /*<<< orphan*/  PHYS_PFN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_dma_entry (struct dma_debug_entry*) ; 
 int /*<<< orphan*/  dma_debug_disabled () ; 
 int /*<<< orphan*/  dma_debug_resource ; 
 struct dma_debug_entry* dma_entry_alloc () ; 
 int /*<<< orphan*/  offset_in_page (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void debug_dma_map_resource(struct device *dev, phys_addr_t addr, size_t size,
			    int direction, dma_addr_t dma_addr)
{
	struct dma_debug_entry *entry;

	if (unlikely(dma_debug_disabled()))
		return;

	entry = dma_entry_alloc();
	if (!entry)
		return;

	entry->type		= dma_debug_resource;
	entry->dev		= dev;
	entry->pfn		= PHYS_PFN(addr);
	entry->offset		= offset_in_page(addr);
	entry->size		= size;
	entry->dev_addr		= dma_addr;
	entry->direction	= direction;
	entry->map_err_type	= MAP_ERR_NOT_CHECKED;

	add_dma_entry(entry);
}