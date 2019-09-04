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
struct TYPE_2__ {int /*<<< orphan*/  writemask; } ;
struct shader_reg {scalar_t__ type; scalar_t__ rel_reg; TYPE_1__ u; int /*<<< orphan*/  regnum; } ;
struct bytecode_buffer {int dummy; } ;
struct bc_writer {scalar_t__ version; int /*<<< orphan*/  state; } ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ BWRITERSPR_OUTPUT ; 
 scalar_t__ BWRITERVS_VERSION (int,int /*<<< orphan*/ ) ; 
 int D3DVS_ADDRESSMODE_MASK ; 
 int D3DVS_ADDRMODE_RELATIVE ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int d3d9_dstmod (int) ; 
 int d3d9_register (scalar_t__) ; 
 int d3d9_writemask (int /*<<< orphan*/ ) ; 
 int d3dsp_register (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_dword (struct bytecode_buffer*,int) ; 
 int /*<<< orphan*/  sm_3_srcreg (struct bc_writer*,scalar_t__,struct bytecode_buffer*) ; 

__attribute__((used)) static void sm_3_dstreg(struct bc_writer *This,
                        const struct shader_reg *reg,
                        struct bytecode_buffer *buffer,
                        DWORD shift, DWORD mod) {
    DWORD token = (1u << 31); /* Bit 31 of registers is 1 */
    DWORD d3d9reg;

    if(reg->rel_reg) {
        if(This->version == BWRITERVS_VERSION(3, 0) &&
           reg->type == BWRITERSPR_OUTPUT) {
            token |= D3DVS_ADDRMODE_RELATIVE & D3DVS_ADDRESSMODE_MASK;
        } else {
            WARN("Relative addressing not supported for this shader type or register type\n");
            This->state = E_INVALIDARG;
            return;
        }
    }

    d3d9reg = d3d9_register(reg->type);
    token |= d3dsp_register( d3d9reg, reg->regnum );
    token |= d3d9_dstmod(mod);
    token |= d3d9_writemask(reg->u.writemask);
    put_dword(buffer, token);

    /* vs_2_0 and newer write the register containing the index explicitly in the
     * binary code
     */
    if(token & D3DVS_ADDRMODE_RELATIVE) {
        sm_3_srcreg(This, reg->rel_reg, buffer);
    }
}