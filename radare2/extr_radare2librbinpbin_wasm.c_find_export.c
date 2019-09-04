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
typedef  scalar_t__ ut32 ;
struct TYPE_3__ {scalar_t__ kind; scalar_t__ const index; } ;
typedef  TYPE_1__ RBinWasmExportEntry ;

/* Variables and functions */
 scalar_t__ R_BIN_WASM_EXTERNALKIND_Function ; 

__attribute__((used)) static bool find_export(const ut32 *p, const RBinWasmExportEntry* q) {
	if (q->kind != R_BIN_WASM_EXTERNALKIND_Function) {
		return true;
	}
	return q->index != (*p);
}