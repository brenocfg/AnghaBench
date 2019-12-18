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
struct TYPE_6__ {scalar_t__ type; } ;
struct instruction {TYPE_2__* src; int /*<<< orphan*/  dstmod; int /*<<< orphan*/  shift; TYPE_3__ dst; } ;
struct bytecode_buffer {int dummy; } ;
struct bc_writer {scalar_t__* t_regnum; scalar_t__* v_regnum; TYPE_1__* funcs; int /*<<< orphan*/  state; } ;
struct TYPE_5__ {scalar_t__ type; scalar_t__ regnum; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* srcreg ) (struct bc_writer*,TYPE_2__*,struct bytecode_buffer*) ;int /*<<< orphan*/  (* dstreg ) (struct bc_writer*,TYPE_3__*,struct bytecode_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* opcode ) (struct bc_writer*,struct instruction const*,int,struct bytecode_buffer*) ;} ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ BWRITERSPR_INPUT ; 
 scalar_t__ BWRITERSPR_TEMP ; 
 int D3DSIO_MOV ; 
 int D3DSIO_TEXCOORD ; 
 int D3DSI_OPCODE_MASK ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  stub1 (struct bc_writer*,struct instruction const*,int,struct bytecode_buffer*) ; 
 int /*<<< orphan*/  stub2 (struct bc_writer*,TYPE_3__*,struct bytecode_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct bc_writer*,TYPE_2__*,struct bytecode_buffer*) ; 

__attribute__((used)) static void instr_ps_1_4_mov(struct bc_writer *This,
                             const struct instruction *instr,
                             struct bytecode_buffer *buffer) {
    DWORD token = D3DSIO_MOV & D3DSI_OPCODE_MASK;

    if(instr->dst.type == BWRITERSPR_TEMP && instr->src[0].type == BWRITERSPR_INPUT) {
        if(instr->src[0].regnum == This->t_regnum[0] ||
           instr->src[0].regnum == This->t_regnum[1] ||
           instr->src[0].regnum == This->t_regnum[2] ||
           instr->src[0].regnum == This->t_regnum[3] ||
           instr->src[0].regnum == This->t_regnum[4] ||
           instr->src[0].regnum == This->t_regnum[5]) {
            /* Similar to a regular mov, but a different opcode */
            token = D3DSIO_TEXCOORD & D3DSI_OPCODE_MASK;
        } else if(instr->src[0].regnum == This->v_regnum[0] ||
                  instr->src[0].regnum == This->v_regnum[1]) {
            /* Handled by the normal mov below. Just drop out of the if condition */
        } else {
            WARN("Unsupported varying -> temp mov in ps_1_4\n");
            This->state = E_INVALIDARG;
            return;
        }
    }

    This->funcs->opcode(This, instr, token, buffer);
    This->funcs->dstreg(This, &instr->dst, buffer, instr->shift, instr->dstmod);
    This->funcs->srcreg(This, &instr->src[0], buffer);
}