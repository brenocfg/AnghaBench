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
typedef  scalar_t__ ut32 ;
struct reloc_struct_t {scalar_t__ data_offset; } ;

/* Variables and functions */

__attribute__((used)) static int search_old_relocation(struct reloc_struct_t *reloc_table,
                                 ut32 addr_to_patch, int n_reloc) {
	int i;
	for (i = 0; i < n_reloc; i++) {
		if (addr_to_patch == reloc_table[i].data_offset) {
			return i;
		}
	}
	return -1;
}