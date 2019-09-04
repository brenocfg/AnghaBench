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
struct shader_reg {int type; TYPE_1__ u; int /*<<< orphan*/  regnum; scalar_t__ rel_reg; } ;
struct bytecode_buffer {int dummy; } ;
struct bc_writer {void* state; int /*<<< orphan*/  version; } ;
typedef  int DWORD ;

/* Variables and functions */
#define  BWRITERSPR_ADDR 135 
#define  BWRITERSPR_ATTROUT 134 
#define  BWRITERSPR_CONST 133 
#define  BWRITERSPR_INPUT 132 
#define  BWRITERSPR_OUTPUT 131 
#define  BWRITERSPR_PREDICATE 130 
#define  BWRITERSPR_RASTOUT 129 
#define  BWRITERSPR_TEMP 128 
 int /*<<< orphan*/  BWRITERVS_VERSION (int,int) ; 
 int D3DSPR_ADDR ; 
 int D3DSPR_PREDICATE ; 
 int D3DSP_DSTSHIFT_MASK ; 
 int D3DSP_DSTSHIFT_SHIFT ; 
 void* E_INVALIDARG ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int d3d9_dstmod (int) ; 
 int d3d9_writemask (int /*<<< orphan*/ ) ; 
 int d3dsp_register (int,int /*<<< orphan*/ ) ; 
 int map_vs_output (struct bc_writer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  put_dword (struct bytecode_buffer*,int) ; 

__attribute__((used)) static void vs_12_dstreg(struct bc_writer *This, const struct shader_reg *reg,
                         struct bytecode_buffer *buffer,
                         DWORD shift, DWORD mod) {
    DWORD token = (1u << 31); /* Bit 31 of registers is 1 */
    DWORD has_wmask;

    if(reg->rel_reg) {
        WARN("Relative addressing not supported for destination registers\n");
        This->state = E_INVALIDARG;
        return;
    }

    switch(reg->type) {
        case BWRITERSPR_OUTPUT:
            token |= map_vs_output(This, reg->regnum, reg->u.writemask, &has_wmask);
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
            token |= d3dsp_register( reg->type, reg->regnum );
            has_wmask = TRUE;
            break;

        case BWRITERSPR_ADDR:
            if(reg->regnum != 0) {
                WARN("Only a0 exists\n");
                This->state = E_INVALIDARG;
                return;
            }
            token |= d3dsp_register( D3DSPR_ADDR, 0 );
            has_wmask = TRUE;
            break;

        case BWRITERSPR_PREDICATE:
            if(This->version != BWRITERVS_VERSION(2, 1)){
                WARN("Predicate register is allowed only in vs_2_x\n");
                This->state = E_INVALIDARG;
                return;
            }
            if(reg->regnum != 0) {
                WARN("Only predicate register p0 exists\n");
                This->state = E_INVALIDARG;
                return;
            }
            token |= d3dsp_register( D3DSPR_PREDICATE, 0 );
            has_wmask = TRUE;
            break;

        default:
            WARN("Invalid register type for 1.x-2.x vertex shader\n");
            This->state = E_INVALIDARG;
            return;
    }

    /* strictly speaking there are no modifiers in vs_2_0 and vs_1_x, but they can be written
     * into the bytecode and since the compiler doesn't do such checks write them
     * (the checks are done by the undocumented shader validator)
     */
    token |= (shift << D3DSP_DSTSHIFT_SHIFT) & D3DSP_DSTSHIFT_MASK;
    token |= d3d9_dstmod(mod);

    if(has_wmask) {
        token |= d3d9_writemask(reg->u.writemask);
    }
    put_dword(buffer, token);
}