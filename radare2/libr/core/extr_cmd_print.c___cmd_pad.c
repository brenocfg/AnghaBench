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
struct TYPE_7__ {int /*<<< orphan*/  assembly; } ;
struct TYPE_6__ {int /*<<< orphan*/ * parser; int /*<<< orphan*/  assembler; int /*<<< orphan*/  config; int /*<<< orphan*/  offset; } ;
typedef  TYPE_1__ RCore ;
typedef  TYPE_2__ RAsmCode ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  r_asm_code_free (TYPE_2__*) ; 
 TYPE_2__* r_asm_mdisassemble_hexstr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  r_asm_set_pc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int r_config_get_i (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_cons_print (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __cmd_pad(RCore *core, const char *arg) {
	if (*arg == '?') {
		eprintf ("Usage: pad [hexpairs] # disassembly given bytes\n");
		return;
	}
	r_asm_set_pc (core->assembler, core->offset);
	bool is_pseudo = r_config_get_i (core->config, "asm.pseudo");
	RAsmCode *acode = r_asm_mdisassemble_hexstr (core->assembler, is_pseudo ? core->parser : NULL, arg);
	if (acode) {
		r_cons_print (acode->assembly);
		r_asm_code_free (acode);
	} else {
		eprintf ("Invalid hexstr\n");
	}
}