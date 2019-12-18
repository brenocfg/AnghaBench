#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * g_names; scalar_t__ g_sections; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  RList ;
typedef  TYPE_1__ RBinWasmSection ;
typedef  TYPE_2__ RBinWasmObj ;

/* Variables and functions */
 int /*<<< orphan*/  R_BIN_WASM_SECTION_CUSTOM ; 
 int /*<<< orphan*/ * r_bin_wasm_get_custom_name_entries (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/ * r_bin_wasm_get_sections_by_id (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ r_list_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_list_new () ; 
 int /*<<< orphan*/  r_return_val_if_fail (int,int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

RList *r_bin_wasm_get_custom_names (RBinWasmObj *bin) {
	RBinWasmSection *cust = NULL;
	RList *customs = NULL;

	r_return_val_if_fail (bin && bin->g_sections, NULL);

	if (bin->g_names) {
		return bin->g_names;
	}
	if (!(customs = r_bin_wasm_get_sections_by_id (bin->g_sections, R_BIN_WASM_SECTION_CUSTOM))) {
		return r_list_new ();
	}
	// support for multiple "name" sections against spec
	if (!(cust = (RBinWasmSection *)r_list_first (customs)) || strncmp (cust->name, "name", 5)) {
		r_list_free (customs);
		return r_list_new ();
	}
	bin->g_names = r_bin_wasm_get_custom_name_entries (bin, cust);
	r_list_free (customs);
	return bin->g_names;
}