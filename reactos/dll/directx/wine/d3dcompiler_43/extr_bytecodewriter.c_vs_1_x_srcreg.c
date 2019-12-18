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
struct TYPE_6__ {int /*<<< orphan*/  swizzle; } ;
struct shader_reg {int type; int /*<<< orphan*/  srcmod; TYPE_3__ u; TYPE_2__* rel_reg; int /*<<< orphan*/  regnum; } ;
struct bytecode_buffer {int dummy; } ;
struct bc_writer {void* state; } ;
struct TYPE_4__ {int const swizzle; } ;
struct TYPE_5__ {int const type; TYPE_1__ u; int /*<<< orphan*/  regnum; } ;
typedef  int DWORD ;

/* Variables and functions */
#define  BWRITERSPR_ADDR 138 
#define  BWRITERSPR_ATTROUT 137 
#define  BWRITERSPR_CONST 136 
#define  BWRITERSPR_INPUT 135 
#define  BWRITERSPR_OUTPUT 134 
#define  BWRITERSPR_RASTOUT 133 
#define  BWRITERSPR_TEMP 132 
 int BWRITERSP_WRITEMASK_0 ; 
 int BWRITERSP_WRITEMASK_1 ; 
 int BWRITERSP_WRITEMASK_2 ; 
 int BWRITERSP_WRITEMASK_3 ; 
#define  BWRITERVS_SWIZZLE_W 131 
#define  BWRITERVS_SWIZZLE_X 130 
#define  BWRITERVS_SWIZZLE_Y 129 
#define  BWRITERVS_SWIZZLE_Z 128 
 int D3DVS_ADDRESSMODE_MASK ; 
 int D3DVS_ADDRMODE_RELATIVE ; 
 int D3DVS_SWIZZLE_MASK ; 
 void* E_INVALIDARG ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int d3d9_srcmod (int /*<<< orphan*/ ) ; 
 int d3d9_swizzle (int /*<<< orphan*/ ) ; 
 int d3dsp_register (int,int /*<<< orphan*/ ) ; 
 int map_vs_output (struct bc_writer*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  put_dword (struct bytecode_buffer*,int) ; 

__attribute__((used)) static void vs_1_x_srcreg(struct bc_writer *This, const struct shader_reg *reg,
                          struct bytecode_buffer *buffer) {
    DWORD token = (1u << 31); /* Bit 31 of registers is 1 */
    DWORD has_swizzle;
    DWORD component;

    switch(reg->type) {
        case BWRITERSPR_OUTPUT:
            /* Map the swizzle to a writemask, the format expected
               by map_vs_output
             */
            switch(reg->u.swizzle) {
                case BWRITERVS_SWIZZLE_X:
                    component = BWRITERSP_WRITEMASK_0;
                    break;
                case BWRITERVS_SWIZZLE_Y:
                    component = BWRITERSP_WRITEMASK_1;
                    break;
                case BWRITERVS_SWIZZLE_Z:
                    component = BWRITERSP_WRITEMASK_2;
                    break;
                case BWRITERVS_SWIZZLE_W:
                    component = BWRITERSP_WRITEMASK_3;
                    break;
                default:
                    component = 0;
            }
            token |= map_vs_output(This, reg->regnum, component, &has_swizzle);
            break;

        case BWRITERSPR_RASTOUT:
        case BWRITERSPR_ATTROUT:
            /* These registers are mapped to input and output regs. They can be encoded in the bytecode,
             * but are unexpected. If we hit this path it might be due to an error.
             */
            FIXME("Unexpected register type %u\n", reg->type);
            /* drop through */
        case BWRITERSPR_INPUT:
        case BWRITERSPR_TEMP:
        case BWRITERSPR_CONST:
        case BWRITERSPR_ADDR:
            token |= d3dsp_register( reg->type, reg->regnum );
            if(reg->rel_reg) {
                if(reg->rel_reg->type != BWRITERSPR_ADDR ||
                   reg->rel_reg->regnum != 0 ||
                   reg->rel_reg->u.swizzle != BWRITERVS_SWIZZLE_X) {
                    WARN("Relative addressing in vs_1_x is only allowed with a0.x\n");
                    This->state = E_INVALIDARG;
                    return;
                }
                token |= D3DVS_ADDRMODE_RELATIVE & D3DVS_ADDRESSMODE_MASK;
            }
            break;

        default:
            WARN("Invalid register type for 1.x vshader\n");
            This->state = E_INVALIDARG;
            return;
    }

    token |= d3d9_swizzle(reg->u.swizzle) & D3DVS_SWIZZLE_MASK; /* already shifted */

    token |= d3d9_srcmod(reg->srcmod);
    put_dword(buffer, token);
}