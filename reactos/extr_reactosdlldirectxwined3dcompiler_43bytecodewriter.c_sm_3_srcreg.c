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
struct TYPE_2__ {int /*<<< orphan*/  swizzle; } ;
struct shader_reg {scalar_t__ type; scalar_t__ regnum; struct shader_reg* rel_reg; int /*<<< orphan*/  srcmod; TYPE_1__ u; } ;
struct bytecode_buffer {int dummy; } ;
struct bc_writer {scalar_t__ version; void* state; } ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ BWRITERPS_VERSION (int,int /*<<< orphan*/ ) ; 
 scalar_t__ BWRITERSPR_ADDR ; 
 scalar_t__ BWRITERSPR_CONST ; 
 scalar_t__ BWRITERSPR_LOOP ; 
 scalar_t__ BWRITERVS_VERSION (int,int /*<<< orphan*/ ) ; 
 int D3DVS_ADDRESSMODE_MASK ; 
 int D3DVS_ADDRMODE_RELATIVE ; 
 int D3DVS_SWIZZLE_MASK ; 
 void* E_INVALIDARG ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 int d3d9_register (scalar_t__) ; 
 int d3d9_srcmod (int /*<<< orphan*/ ) ; 
 int d3d9_swizzle (int /*<<< orphan*/ ) ; 
 int d3dsp_register (int,scalar_t__) ; 
 int /*<<< orphan*/  put_dword (struct bytecode_buffer*,int) ; 

__attribute__((used)) static void sm_3_srcreg(struct bc_writer *This,
                        const struct shader_reg *reg,
                        struct bytecode_buffer *buffer) {
    DWORD token = (1u << 31); /* Bit 31 of registers is 1 */
    DWORD d3d9reg;

    d3d9reg = d3d9_register(reg->type);
    token |= d3dsp_register( d3d9reg, reg->regnum );
    token |= d3d9_swizzle(reg->u.swizzle) & D3DVS_SWIZZLE_MASK;
    token |= d3d9_srcmod(reg->srcmod);

    if(reg->rel_reg) {
        if(reg->type == BWRITERSPR_CONST && This->version == BWRITERPS_VERSION(3, 0)) {
            WARN("c%u[...] is unsupported in ps_3_0\n", reg->regnum);
            This->state = E_INVALIDARG;
            return;
        }
        if(((reg->rel_reg->type == BWRITERSPR_ADDR && This->version == BWRITERVS_VERSION(3, 0)) ||
           reg->rel_reg->type == BWRITERSPR_LOOP) &&
           reg->rel_reg->regnum == 0) {
            token |= D3DVS_ADDRMODE_RELATIVE & D3DVS_ADDRESSMODE_MASK;
        } else {
            WARN("Unsupported relative addressing register\n");
            This->state = E_INVALIDARG;
            return;
        }
    }

    put_dword(buffer, token);

    /* vs_2_0 and newer write the register containing the index explicitly in the
     * binary code
     */
    if(token & D3DVS_ADDRMODE_RELATIVE) {
        sm_3_srcreg(This, reg->rel_reg, buffer);
    }
}