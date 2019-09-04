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
struct shader_reg {int /*<<< orphan*/  srcmod; } ;
struct instruction {struct shader_reg* src; } ;
struct asm_parser {int /*<<< orphan*/  status; int /*<<< orphan*/  line_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  PARSE_ERR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  asmparser_message (struct asm_parser*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_abs_srcmod (struct asm_parser*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_legacy_srcmod (struct asm_parser*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_reg_type (struct shader_reg const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_print_srcreg (struct shader_reg const*) ; 
 struct shader_reg map_oldps_register (struct shader_reg const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ps_2_0_reg_allowed ; 
 int /*<<< orphan*/  set_parse_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asmparser_srcreg_ps_2(struct asm_parser *This,
                                  struct instruction *instr, int num,
                                  const struct shader_reg *src) {
    struct shader_reg reg;

    if(!check_reg_type(src, ps_2_0_reg_allowed)) {
        asmparser_message(This, "Line %u: Source register %s not supported in PS 2.0\n",
                          This->line_no,
                          debug_print_srcreg(src));
        set_parse_status(&This->status, PARSE_ERR);
    }
    check_legacy_srcmod(This, src->srcmod);
    check_abs_srcmod(This, src->srcmod);
    reg = map_oldps_register(src, TRUE);
    instr->src[num] = reg;
}