#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct src_regs {int count; int /*<<< orphan*/ * reg; } ;
struct shader_reg {int dummy; } ;
struct instruction {scalar_t__ comptype; void* shift; void* dstmod; int /*<<< orphan*/  opcode; } ;
struct asm_parser {int /*<<< orphan*/  status; int /*<<< orphan*/  shader; TYPE_1__* funcs; int /*<<< orphan*/  line_no; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* srcreg ) (struct asm_parser*,struct instruction*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* dstreg ) (struct asm_parser*,struct instruction*,struct shader_reg const*) ;} ;
typedef  void* DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  BWRITERSIO_MOV ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  PARSE_ERR ; 
 int /*<<< orphan*/  add_instruction (int /*<<< orphan*/ ,struct instruction*) ; 
 struct instruction* alloc_instr (int) ; 
 int /*<<< orphan*/  asmparser_message (struct asm_parser*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_parse_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct asm_parser*,struct instruction*,struct shader_reg const*) ; 
 int /*<<< orphan*/  stub2 (struct asm_parser*,struct instruction*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void asmparser_texcrd(struct asm_parser *This, DWORD mod, DWORD shift,
                             const struct shader_reg *dst,
                             const struct src_regs *srcs) {
    struct instruction *instr;

    if(!srcs || srcs->count != 1) {
        asmparser_message(This, "Line %u: Wrong number of source registers in texcrd instruction\n", This->line_no);
        set_parse_status(&This->status, PARSE_ERR);
        return;
    }

    instr = alloc_instr(1);
    if(!instr) {
        ERR("Error allocating memory for the instruction\n");
        set_parse_status(&This->status, PARSE_ERR);
        return;
    }

    /* The job of texcrd is done by mov in later shader versions */
    instr->opcode = BWRITERSIO_MOV;
    instr->dstmod = mod;
    instr->shift = shift;
    instr->comptype = 0;

    This->funcs->dstreg(This, instr, dst);
    This->funcs->srcreg(This, instr, 0, &srcs->reg[0]);

    if(!add_instruction(This->shader, instr)) {
        ERR("Out of memory\n");
        set_parse_status(&This->status, PARSE_ERR);
    }
}