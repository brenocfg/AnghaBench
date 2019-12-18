#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  segment_entries; int /*<<< orphan*/  resident_name_table; int /*<<< orphan*/  ne_header; int /*<<< orphan*/  entry_table; int /*<<< orphan*/  resources; } ;
typedef  TYPE_1__ r_bin_ne_obj_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_list_free (int /*<<< orphan*/ ) ; 

void r_bin_ne_free(r_bin_ne_obj_t *bin) {
	// r_list_free (bin->imports); // double free
	r_list_free (bin->resources);
	free (bin->entry_table);
	free (bin->ne_header);
	free (bin->resident_name_table);
	free (bin->segment_entries);
}