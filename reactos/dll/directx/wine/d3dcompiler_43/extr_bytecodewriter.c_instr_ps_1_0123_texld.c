#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int swizzle; } ;
struct shader_reg {scalar_t__ type; int regnum; TYPE_1__ u; } ;
struct TYPE_7__ {scalar_t__ type; int /*<<< orphan*/  regnum; } ;
struct instruction {struct shader_reg* src; int /*<<< orphan*/  dstmod; int /*<<< orphan*/  shift; TYPE_3__ dst; } ;
struct bytecode_buffer {int dummy; } ;
struct bc_writer {int* t_regnum; void* state; TYPE_2__* funcs; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* srcreg ) (struct bc_writer*,struct shader_reg*,struct bytecode_buffer*) ;int /*<<< orphan*/  (* dstreg ) (struct bc_writer*,TYPE_3__*,struct bytecode_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* opcode ) (struct bc_writer*,struct instruction const*,int,struct bytecode_buffer*) ;} ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ BWRITERSPR_INPUT ; 
 scalar_t__ BWRITERSPR_SAMPLER ; 
 scalar_t__ BWRITERSPR_TEMP ; 
 int BWRITERVS_NOSWIZZLE ; 
 int BWRITERVS_SWIZZLE_SHIFT ; 
 int BWRITERVS_W_X ; 
 int BWRITERVS_W_Z ; 
 int BWRITERVS_X_W ; 
 int BWRITERVS_X_X ; 
 int BWRITERVS_X_Y ; 
 int BWRITERVS_Y_X ; 
 int BWRITERVS_Y_Y ; 
 int BWRITERVS_Y_Z ; 
 int BWRITERVS_Z_X ; 
 int BWRITERVS_Z_Z ; 
 int D3DSIO_TEX ; 
 int D3DSIO_TEXREG2AR ; 
 int D3DSIO_TEXREG2GB ; 
 int D3DSIO_TEXREG2RGB ; 
 int D3DSI_OPCODE_MASK ; 
 void* E_INVALIDARG ; 
 int /*<<< orphan*/  T0_REG ; 
 int /*<<< orphan*/  T1_REG ; 
 int /*<<< orphan*/  T2_REG ; 
 int /*<<< orphan*/  T3_REG ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 int /*<<< orphan*/  stub1 (struct bc_writer*,struct instruction const*,int,struct bytecode_buffer*) ; 
 int /*<<< orphan*/  stub2 (struct bc_writer*,TYPE_3__*,struct bytecode_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct bc_writer*,struct instruction const*,int,struct bytecode_buffer*) ; 
 int /*<<< orphan*/  stub4 (struct bc_writer*,struct instruction const*,int,struct bytecode_buffer*) ; 
 int /*<<< orphan*/  stub5 (struct bc_writer*,struct instruction const*,int,struct bytecode_buffer*) ; 
 int /*<<< orphan*/  stub6 (struct bc_writer*,TYPE_3__*,struct bytecode_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (struct bc_writer*,struct shader_reg*,struct bytecode_buffer*) ; 

__attribute__((used)) static void instr_ps_1_0123_texld(struct bc_writer *This,
                                  const struct instruction *instr,
                                  struct bytecode_buffer *buffer) {
    DWORD idx;
    struct shader_reg reg;
    DWORD swizzlemask;

    if(instr->src[1].type != BWRITERSPR_SAMPLER ||
       instr->src[1].regnum > 3) {
        WARN("Unsupported sampler type %u regnum %u\n",
             instr->src[1].type, instr->src[1].regnum);
        This->state = E_INVALIDARG;
        return;
    } else if(instr->dst.type != BWRITERSPR_TEMP) {
        WARN("Can only sample into a temp register\n");
        This->state = E_INVALIDARG;
        return;
    }

    idx = instr->src[1].regnum;
    if((idx == 0 && instr->dst.regnum != T0_REG) ||
       (idx == 1 && instr->dst.regnum != T1_REG) ||
       (idx == 2 && instr->dst.regnum != T2_REG) ||
       (idx == 3 && instr->dst.regnum != T3_REG)) {
        WARN("Sampling from sampler s%u to register r%u is not possible in ps_1_x\n",
             idx, instr->dst.regnum);
        This->state = E_INVALIDARG;
        return;
    }
    if(instr->src[0].type == BWRITERSPR_INPUT) {
        /* A simple non-dependent read tex instruction */
        if(instr->src[0].regnum != This->t_regnum[idx]) {
            WARN("Cannot sample from s%u with texture address data from interpolator %u\n",
                 idx, instr->src[0].regnum);
            This->state = E_INVALIDARG;
            return;
        }
        This->funcs->opcode(This, instr, D3DSIO_TEX & D3DSI_OPCODE_MASK, buffer);

        /* map the temp dstreg to the ps_1_3 texture temporary register */
        This->funcs->dstreg(This, &instr->dst, buffer, instr->shift, instr->dstmod);
    } else if(instr->src[0].type == BWRITERSPR_TEMP) {

        swizzlemask = (3 << BWRITERVS_SWIZZLE_SHIFT) |
            (3 << (BWRITERVS_SWIZZLE_SHIFT + 2)) |
            (3 << (BWRITERVS_SWIZZLE_SHIFT + 4));
        if((instr->src[0].u.swizzle & swizzlemask) == (BWRITERVS_X_X | BWRITERVS_Y_Y | BWRITERVS_Z_Z)) {
            TRACE("writing texreg2rgb\n");
            This->funcs->opcode(This, instr, D3DSIO_TEXREG2RGB & D3DSI_OPCODE_MASK, buffer);
        } else if(instr->src[0].u.swizzle == (BWRITERVS_X_W | BWRITERVS_Y_X | BWRITERVS_Z_X | BWRITERVS_W_X)) {
            TRACE("writing texreg2ar\n");
            This->funcs->opcode(This, instr, D3DSIO_TEXREG2AR & D3DSI_OPCODE_MASK, buffer);
        } else if(instr->src[0].u.swizzle == (BWRITERVS_X_Y | BWRITERVS_Y_Z | BWRITERVS_Z_Z | BWRITERVS_W_Z)) {
            TRACE("writing texreg2gb\n");
            This->funcs->opcode(This, instr, D3DSIO_TEXREG2GB & D3DSI_OPCODE_MASK, buffer);
        } else {
            WARN("Unsupported src addr swizzle in dependent texld: 0x%08x\n", instr->src[0].u.swizzle);
            This->state = E_INVALIDARG;
            return;
        }

        /* Dst and src reg can be mapped normally. Both registers are temporary registers in the
         * source shader and have to be mapped to the temporary form of the texture registers. However,
         * the src reg doesn't have a swizzle
         */
        This->funcs->dstreg(This, &instr->dst, buffer, instr->shift, instr->dstmod);
        reg = instr->src[0];
        reg.u.swizzle = BWRITERVS_NOSWIZZLE;
        This->funcs->srcreg(This, &reg, buffer);
    } else {
        WARN("Invalid address data source register\n");
        This->state = E_INVALIDARG;
        return;
    }
}