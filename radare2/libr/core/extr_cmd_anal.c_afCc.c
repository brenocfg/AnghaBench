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
typedef  long long ut64 ;
typedef  int /*<<< orphan*/  ut32 ;
struct TYPE_3__ {long long offset; int /*<<< orphan*/  anal; int /*<<< orphan*/  num; } ;
typedef  TYPE_1__ RCore ;
typedef  int /*<<< orphan*/  RAnalFunction ;

/* Variables and functions */
 int /*<<< orphan*/  R_ANAL_FCN_TYPE_NULL ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  r_anal_fcn_cost (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_anal_fcn_find_name (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * r_anal_get_fcn_in (int /*<<< orphan*/ ,long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_cons_printf (char*,int /*<<< orphan*/ ) ; 
 long long r_num_math (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void afCc(RCore *core, const char *input) {
	ut64 addr;
	RAnalFunction *fcn;
	if (*input == ' ') {
		addr = r_num_math (core->num, input);
	} else {
		addr = core->offset;
	}
	if (addr == 0LL) {
		fcn = r_anal_fcn_find_name (core->anal, input + 3);
	} else {
		fcn = r_anal_get_fcn_in (core->anal, addr, R_ANAL_FCN_TYPE_NULL);
	}
	if (fcn) {
		ut32 totalCycles = r_anal_fcn_cost (core->anal, fcn);
		// FIXME: This defeats the purpose of the function, but afC is used in project files.
		// cf. canal.c
		r_cons_printf ("%d\n", totalCycles);
	} else {
		eprintf ("afCc: Cannot find function\n");
	}
}