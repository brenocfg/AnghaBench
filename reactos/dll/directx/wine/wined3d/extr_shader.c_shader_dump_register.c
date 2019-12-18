#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wined3d_string_buffer {int dummy; } ;
struct wined3d_shader_version {int major; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {size_t* immconst_data; size_t fp_body_idx; } ;
struct wined3d_shader_register {int type; int immconst_type; size_t data_type; TYPE_2__ u; TYPE_1__* idx; } ;
typedef  size_t UINT ;
struct TYPE_3__ {size_t offset; scalar_t__ rel_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,size_t) ; 
#define  WINED3DSPR_ATTROUT 181 
#define  WINED3DSPR_COLOROUT 180 
#define  WINED3DSPR_CONST 179 
#define  WINED3DSPR_CONST2 178 
#define  WINED3DSPR_CONST3 177 
#define  WINED3DSPR_CONST4 176 
#define  WINED3DSPR_CONSTBOOL 175 
#define  WINED3DSPR_CONSTBUFFER 174 
#define  WINED3DSPR_CONSTINT 173 
#define  WINED3DSPR_COVERAGE 172 
#define  WINED3DSPR_DEPTHOUT 171 
#define  WINED3DSPR_DEPTHOUTGE 170 
#define  WINED3DSPR_DEPTHOUTLE 169 
#define  WINED3DSPR_FORKINSTID 168 
#define  WINED3DSPR_FUNCTIONBODY 167 
#define  WINED3DSPR_FUNCTIONPOINTER 166 
#define  WINED3DSPR_GROUPSHAREDMEM 165 
#define  WINED3DSPR_GSINSTID 164 
#define  WINED3DSPR_IDXTEMP 163 
#define  WINED3DSPR_IMMCONST 162 
#define  WINED3DSPR_IMMCONSTBUFFER 161 
#define  WINED3DSPR_INCONTROLPOINT 160 
#define  WINED3DSPR_INPUT 159 
#define  WINED3DSPR_JOININSTID 158 
#define  WINED3DSPR_LABEL 157 
#define  WINED3DSPR_LOCALTHREADID 156 
#define  WINED3DSPR_LOCALTHREADINDEX 155 
#define  WINED3DSPR_LOOP 154 
#define  WINED3DSPR_MISCTYPE 153 
#define  WINED3DSPR_NULL 152 
#define  WINED3DSPR_OUTCONTROLPOINT 151 
#define  WINED3DSPR_OUTPOINTID 150 
#define  WINED3DSPR_PATCHCONST 149 
#define  WINED3DSPR_PREDICATE 148 
#define  WINED3DSPR_PRIMID 147 
#define  WINED3DSPR_RASTOUT 146 
#define  WINED3DSPR_RESOURCE 145 
#define  WINED3DSPR_SAMPLEMASK 144 
#define  WINED3DSPR_SAMPLER 143 
#define  WINED3DSPR_STREAM 142 
#define  WINED3DSPR_TEMP 141 
#define  WINED3DSPR_TESSCOORD 140 
#define  WINED3DSPR_TEXCRDOUT 139 
#define  WINED3DSPR_TEXTURE 138 
#define  WINED3DSPR_THREADGROUPID 137 
#define  WINED3DSPR_THREADID 136 
#define  WINED3DSPR_UAV 135 
#define  WINED3D_DATA_FLOAT 134 
#define  WINED3D_DATA_INT 133 
#define  WINED3D_DATA_RESOURCE 132 
#define  WINED3D_DATA_SAMPLER 131 
#define  WINED3D_DATA_UINT 130 
#define  WINED3D_IMMCONST_SCALAR 129 
#define  WINED3D_IMMCONST_VEC4 128 
 int /*<<< orphan*/  WINED3D_SHADER_TYPE_PIXEL ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 
 int /*<<< orphan*/  shader_dump_src_param (struct wined3d_string_buffer*,scalar_t__,struct wined3d_shader_version const*) ; 
 size_t shader_get_float_offset (int,size_t) ; 

__attribute__((used)) static void shader_dump_register(struct wined3d_string_buffer *buffer,
        const struct wined3d_shader_register *reg, const struct wined3d_shader_version *shader_version)
{
    static const char * const rastout_reg_names[] = {"oPos", "oFog", "oPts"};
    static const char * const misctype_reg_names[] = {"vPos", "vFace"};
    UINT offset = reg->idx[0].offset;

    switch (reg->type)
    {
        case WINED3DSPR_TEMP:
            shader_addline(buffer, "r");
            break;

        case WINED3DSPR_INPUT:
            shader_addline(buffer, "v");
            break;

        case WINED3DSPR_CONST:
        case WINED3DSPR_CONST2:
        case WINED3DSPR_CONST3:
        case WINED3DSPR_CONST4:
            shader_addline(buffer, "c");
            offset = shader_get_float_offset(reg->type, offset);
            break;

        case WINED3DSPR_TEXTURE: /* vs: case WINED3DSPR_ADDR */
            shader_addline(buffer, "%c", shader_version->type == WINED3D_SHADER_TYPE_PIXEL ? 't' : 'a');
            break;

        case WINED3DSPR_RASTOUT:
            shader_addline(buffer, "%s", rastout_reg_names[offset]);
            break;

        case WINED3DSPR_COLOROUT:
            shader_addline(buffer, "oC");
            break;

        case WINED3DSPR_DEPTHOUT:
            shader_addline(buffer, "oDepth");
            break;

        case WINED3DSPR_DEPTHOUTGE:
            shader_addline(buffer, "oDepthGE");
            break;

        case WINED3DSPR_DEPTHOUTLE:
            shader_addline(buffer, "oDepthLE");
            break;

        case WINED3DSPR_ATTROUT:
            shader_addline(buffer, "oD");
            break;

        case WINED3DSPR_TEXCRDOUT:
            /* Vertex shaders >= 3.0 use general purpose output registers
             * (WINED3DSPR_OUTPUT), which can include an address token. */
            if (shader_version->major >= 3)
                shader_addline(buffer, "o");
            else
                shader_addline(buffer, "oT");
            break;

        case WINED3DSPR_CONSTINT:
            shader_addline(buffer, "i");
            break;

        case WINED3DSPR_CONSTBOOL:
            shader_addline(buffer, "b");
            break;

        case WINED3DSPR_LABEL:
            shader_addline(buffer, "l");
            break;

        case WINED3DSPR_LOOP:
            shader_addline(buffer, "aL");
            break;

        case WINED3DSPR_SAMPLER:
            shader_addline(buffer, "s");
            break;

        case WINED3DSPR_MISCTYPE:
            if (offset > 1)
            {
                FIXME("Unhandled misctype register %u.\n", offset);
                shader_addline(buffer, "<unhandled misctype %#x>", offset);
            }
            else
            {
                shader_addline(buffer, "%s", misctype_reg_names[offset]);
            }
            break;

        case WINED3DSPR_PREDICATE:
            shader_addline(buffer, "p");
            break;

        case WINED3DSPR_IMMCONST:
            shader_addline(buffer, "l");
            break;

        case WINED3DSPR_CONSTBUFFER:
            shader_addline(buffer, "cb");
            break;

        case WINED3DSPR_IMMCONSTBUFFER:
            shader_addline(buffer, "icb");
            break;

        case WINED3DSPR_PRIMID:
            shader_addline(buffer, "primID");
            break;

        case WINED3DSPR_NULL:
            shader_addline(buffer, "null");
            break;

        case WINED3DSPR_RESOURCE:
            shader_addline(buffer, "t");
            break;

        case WINED3DSPR_UAV:
            shader_addline(buffer, "u");
            break;

        case WINED3DSPR_OUTPOINTID:
            shader_addline(buffer, "vOutputControlPointID");
            break;

        case WINED3DSPR_FORKINSTID:
            shader_addline(buffer, "vForkInstanceId");
            break;

        case WINED3DSPR_JOININSTID:
            shader_addline(buffer, "vJoinInstanceId");
            break;

        case WINED3DSPR_INCONTROLPOINT:
            shader_addline(buffer, "vicp");
            break;

        case WINED3DSPR_OUTCONTROLPOINT:
            shader_addline(buffer, "vocp");
            break;

        case WINED3DSPR_PATCHCONST:
            shader_addline(buffer, "vpc");
            break;

        case WINED3DSPR_TESSCOORD:
            shader_addline(buffer, "vDomainLocation");
            break;

        case WINED3DSPR_GROUPSHAREDMEM:
            shader_addline(buffer, "g");
            break;

        case WINED3DSPR_THREADID:
            shader_addline(buffer, "vThreadID");
            break;

        case WINED3DSPR_THREADGROUPID:
            shader_addline(buffer, "vThreadGroupID");
            break;

        case WINED3DSPR_LOCALTHREADID:
            shader_addline(buffer, "vThreadIDInGroup");
            break;

        case WINED3DSPR_LOCALTHREADINDEX:
            shader_addline(buffer, "vThreadIDInGroupFlattened");
            break;

        case WINED3DSPR_IDXTEMP:
            shader_addline(buffer, "x");
            break;

        case WINED3DSPR_STREAM:
            shader_addline(buffer, "m");
            break;

        case WINED3DSPR_FUNCTIONBODY:
            shader_addline(buffer, "fb");
            break;

        case WINED3DSPR_FUNCTIONPOINTER:
            shader_addline(buffer, "fp");
            break;

        case WINED3DSPR_COVERAGE:
            shader_addline(buffer, "vCoverage");
            break;

        case WINED3DSPR_SAMPLEMASK:
            shader_addline(buffer, "oMask");
            break;

        case WINED3DSPR_GSINSTID:
            shader_addline(buffer, "vGSInstanceID");
            break;

        default:
            shader_addline(buffer, "<unhandled_rtype(%#x)>", reg->type);
            break;
    }

    if (reg->type == WINED3DSPR_IMMCONST)
    {
        shader_addline(buffer, "(");
        switch (reg->immconst_type)
        {
            case WINED3D_IMMCONST_SCALAR:
                switch (reg->data_type)
                {
                    case WINED3D_DATA_FLOAT:
                        shader_addline(buffer, "%.8e", *(const float *)reg->u.immconst_data);
                        break;
                    case WINED3D_DATA_INT:
                        shader_addline(buffer, "%d", reg->u.immconst_data[0]);
                        break;
                    case WINED3D_DATA_RESOURCE:
                    case WINED3D_DATA_SAMPLER:
                    case WINED3D_DATA_UINT:
                        shader_addline(buffer, "%u", reg->u.immconst_data[0]);
                        break;
                    default:
                        shader_addline(buffer, "<unhandled data type %#x>", reg->data_type);
                        break;
                }
                break;

            case WINED3D_IMMCONST_VEC4:
                switch (reg->data_type)
                {
                    case WINED3D_DATA_FLOAT:
                        shader_addline(buffer, "%.8e, %.8e, %.8e, %.8e",
                                *(const float *)&reg->u.immconst_data[0], *(const float *)&reg->u.immconst_data[1],
                                *(const float *)&reg->u.immconst_data[2], *(const float *)&reg->u.immconst_data[3]);
                        break;
                    case WINED3D_DATA_INT:
                        shader_addline(buffer, "%d, %d, %d, %d",
                                reg->u.immconst_data[0], reg->u.immconst_data[1],
                                reg->u.immconst_data[2], reg->u.immconst_data[3]);
                        break;
                    case WINED3D_DATA_RESOURCE:
                    case WINED3D_DATA_SAMPLER:
                    case WINED3D_DATA_UINT:
                        shader_addline(buffer, "%u, %u, %u, %u",
                                reg->u.immconst_data[0], reg->u.immconst_data[1],
                                reg->u.immconst_data[2], reg->u.immconst_data[3]);
                        break;
                    default:
                        shader_addline(buffer, "<unhandled data type %#x>", reg->data_type);
                        break;
                }
                break;

            default:
                shader_addline(buffer, "<unhandled immconst_type %#x>", reg->immconst_type);
                break;
        }
        shader_addline(buffer, ")");
    }
    else if (reg->type != WINED3DSPR_RASTOUT
            && reg->type != WINED3DSPR_MISCTYPE
            && reg->type != WINED3DSPR_NULL)
    {
        if (offset != ~0u)
        {
            shader_addline(buffer, "[");
            if (reg->idx[0].rel_addr)
            {
                shader_dump_src_param(buffer, reg->idx[0].rel_addr, shader_version);
                shader_addline(buffer, " + ");
            }
            shader_addline(buffer, "%u]", offset);

            if (reg->idx[1].offset != ~0u)
            {
                shader_addline(buffer, "[");
                if (reg->idx[1].rel_addr)
                {
                    shader_dump_src_param(buffer, reg->idx[1].rel_addr, shader_version);
                    shader_addline(buffer, " + ");
                }
                shader_addline(buffer, "%u]", reg->idx[1].offset);
            }
        }

        if (reg->type == WINED3DSPR_FUNCTIONPOINTER)
            shader_addline(buffer, "[%u]", reg->u.fp_body_idx);
    }
}