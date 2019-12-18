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
struct r_bin_mdmp_obj {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  r_bin_mdmp_init_directory (struct r_bin_mdmp_obj*) ; 
 int /*<<< orphan*/  r_bin_mdmp_init_hdr (struct r_bin_mdmp_obj*) ; 
 int /*<<< orphan*/  r_bin_mdmp_init_parsing (struct r_bin_mdmp_obj*) ; 
 int /*<<< orphan*/  r_bin_mdmp_init_pe_bins (struct r_bin_mdmp_obj*) ; 

__attribute__((used)) static int r_bin_mdmp_init(struct r_bin_mdmp_obj *obj) {
	r_bin_mdmp_init_parsing (obj);

	if (!r_bin_mdmp_init_hdr (obj)) {
		eprintf ("[ERROR] Failed to initialise header\n");
		return false;
	}

	if (!r_bin_mdmp_init_directory (obj)) {
		eprintf ("[ERROR] Failed to initialise directory structures!\n");
		return false;
	}

	if (!r_bin_mdmp_init_pe_bins (obj)) {
		eprintf ("[ERROR] Failed to initialise pe binaries!\n");
		return false;
	}

	return true;
}