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
struct shader_reg {int type; scalar_t__ srcmod; TYPE_1__ u; int /*<<< orphan*/  regnum; scalar_t__ rel_reg; } ;
struct bytecode_buffer {int dummy; } ;
struct bc_writer {void* state; } ;
typedef  int DWORD ;

/* Variables and functions */
#define  BWRITERSPR_CONST 130 
#define  BWRITERSPR_INPUT 129 
#define  BWRITERSPR_TEMP 128 
 scalar_t__ BWRITERSPSM_ABS ; 
 scalar_t__ BWRITERSPSM_ABSNEG ; 
 scalar_t__ BWRITERSPSM_DW ; 
 scalar_t__ BWRITERSPSM_DZ ; 
 scalar_t__ BWRITERSPSM_NOT ; 
 int D3DVS_SWIZZLE_MASK ; 
 void* E_INVALIDARG ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 int d3d9_srcmod (scalar_t__) ; 
 int d3d9_swizzle (int /*<<< orphan*/ ) ; 
 int d3dsp_register (int,int /*<<< orphan*/ ) ; 
 int map_ps13_temp (struct bc_writer*,struct shader_reg const*) ; 
 int map_ps_input (struct bc_writer*,struct shader_reg const*) ; 
 int /*<<< orphan*/  put_dword (struct bytecode_buffer*,int) ; 

__attribute__((used)) static void ps_1_0123_srcreg(struct bc_writer *This, const struct shader_reg *reg,
                             struct bytecode_buffer *buffer) {
    DWORD token = (1u << 31); /* Bit 31 of registers is 1 */
    if(reg->rel_reg) {
        WARN("Relative addressing not supported in <= ps_3_0\n");
        This->state = E_INVALIDARG;
        return;
    }

    switch(reg->type) {
        case BWRITERSPR_INPUT:
            token |= map_ps_input(This, reg);
            break;

            /* Take care about the texture temporaries. There's a problem: They aren't
             * declared anywhere, so we can only hardcode the values that are used
             * to map ps_1_3 shaders to the common shader structure
             */
        case BWRITERSPR_TEMP:
            token |= map_ps13_temp(This, reg);
            break;

        case BWRITERSPR_CONST: /* Can be mapped 1:1 */
            token |= d3dsp_register( reg->type, reg->regnum );
            break;

        default:
            WARN("Invalid register type for <= ps_1_3 shader\n");
            This->state = E_INVALIDARG;
            return;
    }

    token |= d3d9_swizzle(reg->u.swizzle) & D3DVS_SWIZZLE_MASK; /* already shifted */

    if(reg->srcmod == BWRITERSPSM_DZ || reg->srcmod == BWRITERSPSM_DW ||
       reg->srcmod == BWRITERSPSM_ABS || reg->srcmod == BWRITERSPSM_ABSNEG ||
       reg->srcmod == BWRITERSPSM_NOT) {
        WARN("Invalid source modifier %u for <= ps_1_3\n", reg->srcmod);
        This->state = E_INVALIDARG;
        return;
    }
    token |= d3d9_srcmod(reg->srcmod);
    put_dword(buffer, token);
}