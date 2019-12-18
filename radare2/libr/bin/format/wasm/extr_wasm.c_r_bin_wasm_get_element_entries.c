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
typedef  int /*<<< orphan*/  RListFree ;
typedef  int /*<<< orphan*/  RList ;
typedef  int /*<<< orphan*/  RBinWasmSection ;
typedef  int /*<<< orphan*/  RBinWasmObj ;

/* Variables and functions */
 scalar_t__ free ; 
 int /*<<< orphan*/ * get_entries_from_section (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_element_entry ; 

__attribute__((used)) static RList *r_bin_wasm_get_element_entries (RBinWasmObj *bin, RBinWasmSection *sec) {
	return get_entries_from_section (bin, sec, parse_element_entry, (RListFree)free);
}