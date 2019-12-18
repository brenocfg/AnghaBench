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
struct shader_reg {int dummy; } ;
struct instruction {int /*<<< orphan*/  has_dst; int /*<<< orphan*/  dst; scalar_t__ comptype; scalar_t__ shift; scalar_t__ dstmod; int /*<<< orphan*/  opcode; } ;
struct asm_parser {int /*<<< orphan*/  status; int /*<<< orphan*/  shader; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWRITERSIO_TEXKILL ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  PARSE_ERR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  add_instruction (int /*<<< orphan*/ ,struct instruction*) ; 
 struct instruction* alloc_instr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_oldps_register (struct shader_reg const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_parse_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asmparser_texkill(struct asm_parser *This,
                              const struct shader_reg *dst) {
    struct instruction *instr = alloc_instr(0);

    if(!instr) {
        ERR("Error allocating memory for the instruction\n");
        set_parse_status(&This->status, PARSE_ERR);
        return;
    }

    instr->opcode = BWRITERSIO_TEXKILL;
    instr->dstmod = 0;
    instr->shift = 0;
    instr->comptype = 0;

    /* Do not run the dst register through the normal
     * register conversion. If used with ps_1_0 to ps_1_3
     * the texture coordinate from that register is used,
     * not the temporary register value. In ps_1_4 and
     * ps_2_0 t0 is always a varying and temporaries can
     * be used with texkill.
     */
    instr->dst = map_oldps_register(dst, TRUE);
    instr->has_dst = TRUE;

    if(!add_instruction(This->shader, instr)) {
        ERR("Out of memory\n");
        set_parse_status(&This->status, PARSE_ERR);
    }
}