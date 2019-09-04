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
struct r_bin_te_obj_t {scalar_t__ endian; int /*<<< orphan*/ * section_header; int /*<<< orphan*/ * header; } ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  r_bin_te_init_hdr (struct r_bin_te_obj_t*) ; 
 int /*<<< orphan*/  r_bin_te_init_sections (struct r_bin_te_obj_t*) ; 

__attribute__((used)) static int r_bin_te_init(struct r_bin_te_obj_t* bin) {
	bin->header = NULL;
	bin->section_header = NULL;
	bin->endian = 0;
	if (!r_bin_te_init_hdr (bin)) {
		eprintf("Warning: File is not TE\n");
		return false;
	}
	if (!r_bin_te_init_sections (bin)) {
		eprintf("Warning: Cannot initialize sections\n");
		return false;
	}
	return true;
}