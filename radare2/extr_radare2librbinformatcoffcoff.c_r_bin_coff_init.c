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
struct r_bin_coff_obj {int verbose; int /*<<< orphan*/  size; int /*<<< orphan*/  b; } ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  bprintf (char*) ; 
 int /*<<< orphan*/  r_bin_coff_init_hdr (struct r_bin_coff_obj*) ; 
 int /*<<< orphan*/  r_bin_coff_init_opt_hdr (struct r_bin_coff_obj*) ; 
 int /*<<< orphan*/  r_bin_coff_init_scn_hdr (struct r_bin_coff_obj*) ; 
 int /*<<< orphan*/  r_bin_coff_init_symtable (struct r_bin_coff_obj*) ; 
 int /*<<< orphan*/  r_buf_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_buf_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int r_bin_coff_init(struct r_bin_coff_obj *obj, RBuffer *buf, bool verbose) {
	obj->b = r_buf_ref (buf);
	obj->size = r_buf_size (buf);
	obj->verbose = verbose;
	if (!r_bin_coff_init_hdr (obj)) {
		bprintf ("Warning: failed to init hdr\n");
		return false;
	}
	r_bin_coff_init_opt_hdr (obj);
	if (!r_bin_coff_init_scn_hdr (obj)) {
		bprintf ("Warning: failed to init section header\n");
		return false;
	}
	if (!r_bin_coff_init_symtable (obj)) {
		bprintf ("Warning: failed to init symtable\n");
		return false;
	}
	return true;
}