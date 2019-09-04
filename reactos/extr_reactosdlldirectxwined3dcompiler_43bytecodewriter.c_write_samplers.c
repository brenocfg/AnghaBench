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
struct bytecode_buffer {int dummy; } ;
struct bwriter_shader {size_t num_samplers; TYPE_1__* samplers; } ;
struct TYPE_2__ {size_t const regnum; int /*<<< orphan*/  mod; int /*<<< orphan*/  type; } ;
typedef  size_t DWORD ;

/* Variables and functions */
 int D3DSIO_DCL ; 
 int D3DSI_INSTLENGTH_SHIFT ; 
 int /*<<< orphan*/  D3DSPR_SAMPLER ; 
 size_t const D3DSP_REGNUM_MASK ; 
 size_t D3DSP_TEXTURETYPE_MASK ; 
 unsigned int D3DSP_WRITEMASK_ALL ; 
 size_t d3d9_dstmod (int /*<<< orphan*/ ) ; 
 size_t d3d9_sampler (int /*<<< orphan*/ ) ; 
 unsigned int d3dsp_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_dword (struct bytecode_buffer*,size_t) ; 

__attribute__((used)) static void write_samplers(const struct bwriter_shader *shader, struct bytecode_buffer *buffer) {
    DWORD i;
    DWORD instr_dcl = D3DSIO_DCL | (2 << D3DSI_INSTLENGTH_SHIFT);
    DWORD token;
    const DWORD reg = (1u << 31) | d3dsp_register( D3DSPR_SAMPLER, 0 ) | D3DSP_WRITEMASK_ALL;

    for(i = 0; i < shader->num_samplers; i++) {
        /* Write the DCL instruction */
        put_dword(buffer, instr_dcl);
        token = (1u << 31);
        /* Already shifted */
        token |= (d3d9_sampler(shader->samplers[i].type)) & D3DSP_TEXTURETYPE_MASK;
        put_dword(buffer, token);
        token = reg | (shader->samplers[i].regnum & D3DSP_REGNUM_MASK);
        token |= d3d9_dstmod(shader->samplers[i].mod);
        put_dword(buffer, token);
    }
}