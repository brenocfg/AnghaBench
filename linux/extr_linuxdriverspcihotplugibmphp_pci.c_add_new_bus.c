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
typedef  int u8 ;
struct resource_node {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct range_node {int rangeno; int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct bus_node {int noIORanges; int noMemRanges; int noPFMemRanges; struct range_node* rangePFMem; struct range_node* rangeMem; struct range_node* rangeIO; int /*<<< orphan*/  bus_list; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  err (char*) ; 
 struct bus_node* ibmphp_find_res_bus (int) ; 
 struct range_node* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int add_new_bus(struct bus_node *bus, struct resource_node *io, struct resource_node *mem, struct resource_node *pfmem, u8 parent_busno)
{
	struct range_node *io_range = NULL;
	struct range_node *mem_range = NULL;
	struct range_node *pfmem_range = NULL;
	struct bus_node *cur_bus = NULL;

	/* Trying to find the parent bus number */
	if (parent_busno != 0xFF) {
		cur_bus	= ibmphp_find_res_bus(parent_busno);
		if (!cur_bus) {
			err("strange, cannot find bus which is supposed to be at the system... something is terribly wrong...\n");
			return -ENODEV;
		}

		list_add(&bus->bus_list, &cur_bus->bus_list);
	}
	if (io) {
		io_range = kzalloc(sizeof(*io_range), GFP_KERNEL);
		if (!io_range)
			return -ENOMEM;

		io_range->start = io->start;
		io_range->end = io->end;
		io_range->rangeno = 1;
		bus->noIORanges = 1;
		bus->rangeIO = io_range;
	}
	if (mem) {
		mem_range = kzalloc(sizeof(*mem_range), GFP_KERNEL);
		if (!mem_range)
			return -ENOMEM;

		mem_range->start = mem->start;
		mem_range->end = mem->end;
		mem_range->rangeno = 1;
		bus->noMemRanges = 1;
		bus->rangeMem = mem_range;
	}
	if (pfmem) {
		pfmem_range = kzalloc(sizeof(*pfmem_range), GFP_KERNEL);
		if (!pfmem_range)
			return -ENOMEM;

		pfmem_range->start = pfmem->start;
		pfmem_range->end = pfmem->end;
		pfmem_range->rangeno = 1;
		bus->noPFMemRanges = 1;
		bus->rangePFMem = pfmem_range;
	}
	return 0;
}