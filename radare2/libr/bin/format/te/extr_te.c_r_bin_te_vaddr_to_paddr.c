#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct r_bin_te_obj_t {TYPE_2__* section_header; TYPE_1__* header; } ;
struct TYPE_4__ {scalar_t__ VirtualAddress; int VirtualSize; scalar_t__ PointerToRawData; } ;
struct TYPE_3__ {int NumberOfSections; } ;
typedef  scalar_t__ TE_DWord ;

/* Variables and functions */

__attribute__((used)) static TE_DWord r_bin_te_vaddr_to_paddr(struct r_bin_te_obj_t* bin, TE_DWord vaddr) {
	TE_DWord section_base;
	int i, section_size;

	for (i = 0; i < bin->header->NumberOfSections; i++) {
		section_base = bin->section_header[i].VirtualAddress;
		section_size = bin->section_header[i].VirtualSize;
		if (vaddr >= section_base && vaddr < section_base + section_size) {
			return bin->section_header[i].PointerToRawData + (vaddr - section_base);
		}
	}
	return 0;
}