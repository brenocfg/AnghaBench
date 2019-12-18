#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * g_exports; int /*<<< orphan*/  g_sections; } ;
typedef  int /*<<< orphan*/  RList ;
typedef  int /*<<< orphan*/  RBinWasmSection ;
typedef  TYPE_1__ RBinWasmObj ;

/* Variables and functions */
 int /*<<< orphan*/  R_BIN_WASM_SECTION_EXPORT ; 
 int /*<<< orphan*/ * r_bin_wasm_get_export_entries (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_bin_wasm_get_sections_by_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ r_list_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_list_new () ; 

RList *r_bin_wasm_get_exports (RBinWasmObj *bin) {
	RBinWasmSection *export = NULL;
	RList *exports = NULL;

	if (!bin || !bin->g_sections) {
		return NULL;
	}
	if (bin->g_exports) {
		return bin->g_exports;
	}
	if (!(exports = r_bin_wasm_get_sections_by_id (bin->g_sections, R_BIN_WASM_SECTION_EXPORT))) {
		return r_list_new ();
	}
	// support for multiple export sections against spec
	if (!(export = (RBinWasmSection *)r_list_first (exports))) {
		r_list_free (exports);
		return r_list_new ();
	}
	bin->g_exports = r_bin_wasm_get_export_entries (bin, export);
	r_list_free (exports);
	return bin->g_exports;
}