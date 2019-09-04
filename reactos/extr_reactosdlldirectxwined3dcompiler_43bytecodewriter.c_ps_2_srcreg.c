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
struct shader_reg {int type; int /*<<< orphan*/  srcmod; TYPE_1__ u; int /*<<< orphan*/  regnum; scalar_t__ rel_reg; } ;
struct bytecode_buffer {int dummy; } ;
struct bc_writer {void* state; int /*<<< orphan*/  version; } ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  BWRITERPS_VERSION (int,int) ; 
#define  BWRITERSPR_COLOROUT 137 
#define  BWRITERSPR_CONST 136 
#define  BWRITERSPR_CONSTBOOL 135 
#define  BWRITERSPR_CONSTINT 134 
#define  BWRITERSPR_DEPTHOUT 133 
#define  BWRITERSPR_INPUT 132 
#define  BWRITERSPR_LABEL 131 
#define  BWRITERSPR_PREDICATE 130 
#define  BWRITERSPR_SAMPLER 129 
#define  BWRITERSPR_TEMP 128 
 int D3DSPR_PREDICATE ; 
 int D3DVS_SWIZZLE_MASK ; 
 void* E_INVALIDARG ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 int d3d9_register (int) ; 
 int d3d9_srcmod (int /*<<< orphan*/ ) ; 
 int d3d9_swizzle (int /*<<< orphan*/ ) ; 
 int d3dsp_register (int,int /*<<< orphan*/ ) ; 
 int map_ps_input (struct bc_writer*,struct shader_reg const*) ; 
 int /*<<< orphan*/  put_dword (struct bytecode_buffer*,int) ; 

__attribute__((used)) static void ps_2_srcreg(struct bc_writer *This,
                        const struct shader_reg *reg,
                        struct bytecode_buffer *buffer) {
    DWORD token = (1u << 31); /* Bit 31 of registers is 1 */
    DWORD d3d9reg;
    if(reg->rel_reg) {
        WARN("Relative addressing not supported in <= ps_3_0\n");
        This->state = E_INVALIDARG;
        return;
    }

    switch(reg->type) {
        case BWRITERSPR_INPUT:
            token |= map_ps_input(This, reg);
            break;

            /* Can be mapped 1:1 */
        case BWRITERSPR_TEMP:
        case BWRITERSPR_CONST:
        case BWRITERSPR_COLOROUT:
        case BWRITERSPR_CONSTBOOL:
        case BWRITERSPR_CONSTINT:
        case BWRITERSPR_SAMPLER:
        case BWRITERSPR_LABEL:
        case BWRITERSPR_DEPTHOUT:
            d3d9reg = d3d9_register(reg->type);
            token |= d3dsp_register( d3d9reg, reg->regnum );
            break;

        case BWRITERSPR_PREDICATE:
            if(This->version != BWRITERPS_VERSION(2, 1)){
                WARN("Predicate register not supported in ps_2_0\n");
                This->state = E_INVALIDARG;
            }
            if(reg->regnum) {
                WARN("Predicate register with regnum %u not supported\n",
                     reg->regnum);
                This->state = E_INVALIDARG;
            }
            token |= d3dsp_register( D3DSPR_PREDICATE, 0 );
            break;

        default:
            WARN("Invalid register type for ps_2_0 shader\n");
            This->state = E_INVALIDARG;
            return;
    }

    token |= d3d9_swizzle(reg->u.swizzle) & D3DVS_SWIZZLE_MASK; /* already shifted */

    token |= d3d9_srcmod(reg->srcmod);
    put_dword(buffer, token);
}