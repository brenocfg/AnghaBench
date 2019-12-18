#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut32 ;
struct TYPE_6__ {int /*<<< orphan*/  atoms; } ;
typedef  TYPE_1__ EsilCfgGen ;

/* Variables and functions */
 int /*<<< orphan*/  _handle_else_enter (TYPE_1__*,scalar_t__,int) ; 
 int /*<<< orphan*/  _handle_fi_leave (TYPE_1__*,scalar_t__,int) ; 
 int /*<<< orphan*/  _handle_if_enter (TYPE_1__*,scalar_t__,int) ; 
 int /*<<< orphan*/  r_id_storage_get (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

void _handle_control_flow_ifelsefi (EsilCfgGen *gen, char *atom, ut32 id) {
	// we're probably going to see more ?{ and }, than }{
	// so checking against ?{ and } befor }{ is therefor better for perf (lololol)
	if (!strcmp (atom, "?{")) {
		_handle_if_enter (gen, id, !!r_id_storage_get (gen->atoms, id + 1));
		return;
	}
	if (!strcmp (atom, "}")) {
		_handle_fi_leave (gen, id, !!r_id_storage_get (gen->atoms, id + 1));
		return;
	}
	if (!strcmp (atom, "}{")) {
		_handle_else_enter (gen, id, !!r_id_storage_get (gen->atoms, id + 1));
	}
}