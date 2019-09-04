#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  writemask; } ;
struct shader_reg {TYPE_2__ u; int /*<<< orphan*/  regnum; } ;
struct instruction {scalar_t__ shift; scalar_t__ dstmod; } ;
struct asm_parser {int /*<<< orphan*/  status; TYPE_3__* shader; TYPE_1__* funcs; int /*<<< orphan*/  line_no; } ;
struct TYPE_6__ {scalar_t__ version; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* dstreg ) (struct asm_parser*,struct instruction*,struct shader_reg const*) ;} ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ BWRITERPS_VERSION (int,int /*<<< orphan*/ ) ; 
 scalar_t__ BWRITERSPDM_MSAMPCENTROID ; 
 scalar_t__ BWRITERSPDM_PARTIALPRECISION ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PARSE_ERR ; 
 int /*<<< orphan*/  asmparser_message (struct asm_parser*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  record_declaration (TYPE_3__*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_parse_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct asm_parser*,struct instruction*,struct shader_reg const*) ; 

__attribute__((used)) static void asmparser_dcl_input(struct asm_parser *This, DWORD usage, DWORD num,
                                DWORD mod, const struct shader_reg *reg) {
    struct instruction instr;

    if(!This->shader) return;
    if(mod != 0 &&
       (This->shader->version != BWRITERPS_VERSION(3, 0) ||
        (mod != BWRITERSPDM_MSAMPCENTROID &&
         mod != BWRITERSPDM_PARTIALPRECISION))) {
        asmparser_message(This, "Line %u: Unsupported modifier in dcl instruction\n", This->line_no);
        set_parse_status(&This->status, PARSE_ERR);
        return;
    }

    /* Check register type and modifiers */
    instr.dstmod = mod;
    instr.shift = 0;
    This->funcs->dstreg(This, &instr, reg);

    if(!record_declaration(This->shader, usage, num, mod, FALSE, reg->regnum, reg->u.writemask, FALSE)) {
        ERR("Out of memory\n");
        set_parse_status(&This->status, PARSE_ERR);
    }
}