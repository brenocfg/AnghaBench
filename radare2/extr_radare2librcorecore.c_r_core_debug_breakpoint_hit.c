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
struct TYPE_7__ {char const* data; } ;
struct TYPE_6__ {int /*<<< orphan*/  config; } ;
typedef  TYPE_1__ RCore ;
typedef  TYPE_2__ RBreakpointItem ;

/* Variables and functions */
 char* r_config_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_cons_flush () ; 
 int /*<<< orphan*/  r_cons_pop () ; 
 int /*<<< orphan*/  r_cons_push () ; 
 int /*<<< orphan*/  r_core_cmd0 (TYPE_1__*,char const*) ; 

__attribute__((used)) static void r_core_debug_breakpoint_hit(RCore *core, RBreakpointItem *bpi) {
	const char *cmdbp = r_config_get (core->config, "cmd.bp");
	const bool cmdbp_exists = (cmdbp && *cmdbp);
	const bool bpcmd_exists = (bpi->data && bpi->data[0]);
	const bool may_output = (cmdbp_exists || bpcmd_exists);
	if (may_output) {
		r_cons_push ();
	}
	if (cmdbp_exists) {
		r_core_cmd0 (core, cmdbp);
	}
	if (bpcmd_exists) {
		r_core_cmd0 (core, bpi->data);
	}
	if (may_output) {
		r_cons_flush ();
		r_cons_pop ();
	}
}