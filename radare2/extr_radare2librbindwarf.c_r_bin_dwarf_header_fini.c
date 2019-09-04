#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* name; } ;
struct TYPE_4__ {size_t file_names_count; TYPE_3__* file_names; TYPE_3__* std_opcode_lengths; } ;
typedef  TYPE_1__ RBinDwarfLNPHeader ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_3__*) ; 

__attribute__((used)) static void r_bin_dwarf_header_fini(RBinDwarfLNPHeader *hdr) {
	if (hdr) {
		size_t i;

		for (i = 0; i < hdr->file_names_count; i ++) {
			free (hdr->file_names[i].name);
		}

		free (hdr->std_opcode_lengths);
		free (hdr->file_names);
	}
}