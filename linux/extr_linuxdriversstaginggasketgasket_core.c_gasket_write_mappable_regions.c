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
typedef  scalar_t__ ulong ;
struct gasket_driver_desc {scalar_t__ legacy_mmap_address_offset; struct gasket_bar_desc* bar_descriptions; } ;
struct gasket_bar_desc {scalar_t__ permissions; int num_mappable_regions; TYPE_1__* mappable_regions; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_2__ {scalar_t__ length_bytes; scalar_t__ start; } ;

/* Variables and functions */
 scalar_t__ GASKET_NOMAP ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ scnprintf (char*,scalar_t__,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static ssize_t
gasket_write_mappable_regions(char *buf,
			      const struct gasket_driver_desc *driver_desc,
			      int bar_index)
{
	int i;
	ssize_t written;
	ssize_t total_written = 0;
	ulong min_addr, max_addr;
	struct gasket_bar_desc bar_desc =
		driver_desc->bar_descriptions[bar_index];

	if (bar_desc.permissions == GASKET_NOMAP)
		return 0;
	for (i = 0;
	     i < bar_desc.num_mappable_regions && total_written < PAGE_SIZE;
	     i++) {
		min_addr = bar_desc.mappable_regions[i].start -
			   driver_desc->legacy_mmap_address_offset;
		max_addr = bar_desc.mappable_regions[i].start -
			   driver_desc->legacy_mmap_address_offset +
			   bar_desc.mappable_regions[i].length_bytes;
		written = scnprintf(buf, PAGE_SIZE - total_written,
				    "0x%08lx-0x%08lx\n", min_addr, max_addr);
		total_written += written;
		buf += written;
	}
	return total_written;
}