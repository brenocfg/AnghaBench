#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wined3d_shader_register {int type; TYPE_4__* idx; } ;
struct wined3d_shader_reg_maps {unsigned int texcoord; unsigned int address; unsigned int temporary; int input_rel_addressing; unsigned int input_registers; int fog; int point_size; int vpos; int usesfacing; int min_rel_offset; int max_rel_offset; unsigned int integer_constants; unsigned int boolean_constants; unsigned int rt_mask; int vocp; int /*<<< orphan*/  constf; int /*<<< orphan*/  usesrelconstF; } ;
struct TYPE_5__ {unsigned int input_reg_used; } ;
struct TYPE_6__ {TYPE_1__ ps; } ;
struct wined3d_shader {TYPE_3__* limits; TYPE_2__ u; } ;
typedef  enum wined3d_shader_type { ____Placeholder_wined3d_shader_type } wined3d_shader_type ;
struct TYPE_8__ {unsigned int offset; int /*<<< orphan*/  rel_addr; } ;
struct TYPE_7__ {int constant_int; unsigned int constant_bool; int /*<<< orphan*/  constant_float; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRACE (char*,int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*,int) ; 
#define  WINED3DSPR_COLOROUT 137 
#define  WINED3DSPR_CONST 136 
#define  WINED3DSPR_CONSTBOOL 135 
#define  WINED3DSPR_CONSTINT 134 
#define  WINED3DSPR_INPUT 133 
#define  WINED3DSPR_MISCTYPE 132 
#define  WINED3DSPR_OUTCONTROLPOINT 131 
#define  WINED3DSPR_RASTOUT 130 
#define  WINED3DSPR_TEMP 129 
#define  WINED3DSPR_TEXTURE 128 
 int WINED3D_SHADER_TYPE_PIXEL ; 
 int min (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  wined3d_insert_bits (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static BOOL shader_record_register_usage(struct wined3d_shader *shader, struct wined3d_shader_reg_maps *reg_maps,
        const struct wined3d_shader_register *reg, enum wined3d_shader_type shader_type, unsigned int constf_size)
{
    switch (reg->type)
    {
        case WINED3DSPR_TEXTURE: /* WINED3DSPR_ADDR */
            if (shader_type == WINED3D_SHADER_TYPE_PIXEL)
                reg_maps->texcoord |= 1u << reg->idx[0].offset;
            else
                reg_maps->address |= 1u << reg->idx[0].offset;
            break;

        case WINED3DSPR_TEMP:
            reg_maps->temporary |= 1u << reg->idx[0].offset;
            break;

        case WINED3DSPR_INPUT:
            if (reg->idx[0].rel_addr)
                reg_maps->input_rel_addressing = 1;
            if (shader_type == WINED3D_SHADER_TYPE_PIXEL)
            {
                /* If relative addressing is used, we must assume that all
                 * registers are used. Even if it is a construct like v3[aL],
                 * we can't assume that v0, v1 and v2 aren't read because aL
                 * can be negative. */
                if (reg->idx[0].rel_addr)
                    shader->u.ps.input_reg_used = ~0u;
                else
                    shader->u.ps.input_reg_used |= 1u << reg->idx[0].offset;
            }
            else
            {
                reg_maps->input_registers |= 1u << reg->idx[0].offset;
            }
            break;

        case WINED3DSPR_RASTOUT:
            if (reg->idx[0].offset == 1)
                reg_maps->fog = 1;
            if (reg->idx[0].offset == 2)
                reg_maps->point_size = 1;
            break;

        case WINED3DSPR_MISCTYPE:
            if (shader_type == WINED3D_SHADER_TYPE_PIXEL)
            {
                if (!reg->idx[0].offset)
                    reg_maps->vpos = 1;
                else if (reg->idx[0].offset == 1)
                    reg_maps->usesfacing = 1;
            }
            break;

        case WINED3DSPR_CONST:
            if (reg->idx[0].rel_addr)
            {
                if (reg->idx[0].offset < reg_maps->min_rel_offset)
                    reg_maps->min_rel_offset = reg->idx[0].offset;
                if (reg->idx[0].offset > reg_maps->max_rel_offset)
                    reg_maps->max_rel_offset = reg->idx[0].offset;
                reg_maps->usesrelconstF = TRUE;
            }
            else
            {
                if (reg->idx[0].offset >= min(shader->limits->constant_float, constf_size))
                {
                    WARN("Shader using float constant %u which is not supported.\n", reg->idx[0].offset);
                    return FALSE;
                }
                else
                {
                    wined3d_insert_bits(reg_maps->constf, reg->idx[0].offset, 1, 0x1);
                }
            }
            break;

        case WINED3DSPR_CONSTINT:
            if (reg->idx[0].offset >= shader->limits->constant_int)
            {
                WARN("Shader using integer constant %u which is not supported.\n", reg->idx[0].offset);
                return FALSE;
            }
            else
            {
                reg_maps->integer_constants |= (1u << reg->idx[0].offset);
            }
            break;

        case WINED3DSPR_CONSTBOOL:
            if (reg->idx[0].offset >= shader->limits->constant_bool)
            {
                WARN("Shader using bool constant %u which is not supported.\n", reg->idx[0].offset);
                return FALSE;
            }
            else
            {
                reg_maps->boolean_constants |= (1u << reg->idx[0].offset);
            }
            break;

        case WINED3DSPR_COLOROUT:
            reg_maps->rt_mask |= (1u << reg->idx[0].offset);
            break;

        case WINED3DSPR_OUTCONTROLPOINT:
            reg_maps->vocp = 1;
            break;

        default:
            TRACE("Not recording register of type %#x and [%#x][%#x].\n",
                    reg->type, reg->idx[0].offset, reg->idx[1].offset);
            break;
    }
    return TRUE;
}