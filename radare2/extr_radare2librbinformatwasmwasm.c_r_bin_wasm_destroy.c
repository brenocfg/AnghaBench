#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* o; } ;
struct TYPE_7__ {struct TYPE_7__* g_start; int /*<<< orphan*/  g_datas; int /*<<< orphan*/  g_codes; int /*<<< orphan*/  g_globals; int /*<<< orphan*/  g_memories; int /*<<< orphan*/  g_tables; int /*<<< orphan*/  g_exports; int /*<<< orphan*/  g_imports; int /*<<< orphan*/  g_types; int /*<<< orphan*/  g_sections; int /*<<< orphan*/  buf; } ;
struct TYPE_6__ {TYPE_2__* bin_obj; } ;
typedef  TYPE_2__ RBinWasmObj ;
typedef  TYPE_3__ RBinFile ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  r_buf_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_list_free (int /*<<< orphan*/ ) ; 

void r_bin_wasm_destroy (RBinFile *bf) {
	RBinWasmObj *bin;

	if (!bf || !bf->o || !bf->o->bin_obj) {
		return;
	}

	bin = bf->o->bin_obj;
	r_buf_free (bin->buf);

	r_list_free (bin->g_sections);
	r_list_free (bin->g_types);

	r_list_free (bin->g_imports);
	r_list_free (bin->g_exports);
	r_list_free (bin->g_tables);
	r_list_free (bin->g_memories);
	r_list_free (bin->g_globals);
	r_list_free (bin->g_codes);
	r_list_free (bin->g_datas);

	free (bin->g_start);
	free (bin);
	bf->o->bin_obj = NULL;
}