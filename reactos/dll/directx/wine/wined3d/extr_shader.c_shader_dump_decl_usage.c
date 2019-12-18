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
struct wined3d_shader_version {int major; scalar_t__ type; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct TYPE_4__ {TYPE_1__ reg; } ;
struct wined3d_shader_semantic {int resource_type; int resource_data_type; int usage; int usage_idx; TYPE_2__ reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
 scalar_t__ WINED3DSPR_RESOURCE ; 
 scalar_t__ WINED3DSPR_SAMPLER ; 
 scalar_t__ WINED3DSPR_UAV ; 
#define  WINED3D_DATA_FLOAT 156 
#define  WINED3D_DATA_INT 155 
#define  WINED3D_DATA_SNORM 154 
#define  WINED3D_DATA_UINT 153 
#define  WINED3D_DATA_UNORM 152 
#define  WINED3D_DECL_USAGE_BINORMAL 151 
#define  WINED3D_DECL_USAGE_BLEND_INDICES 150 
#define  WINED3D_DECL_USAGE_BLEND_WEIGHT 149 
#define  WINED3D_DECL_USAGE_COLOR 148 
#define  WINED3D_DECL_USAGE_DEPTH 147 
#define  WINED3D_DECL_USAGE_FOG 146 
#define  WINED3D_DECL_USAGE_NORMAL 145 
#define  WINED3D_DECL_USAGE_POSITION 144 
#define  WINED3D_DECL_USAGE_POSITIONT 143 
#define  WINED3D_DECL_USAGE_PSIZE 142 
#define  WINED3D_DECL_USAGE_SAMPLE 141 
#define  WINED3D_DECL_USAGE_TANGENT 140 
#define  WINED3D_DECL_USAGE_TESS_FACTOR 139 
#define  WINED3D_DECL_USAGE_TEXCOORD 138 
#define  WINED3D_SHADER_RESOURCE_BUFFER 137 
#define  WINED3D_SHADER_RESOURCE_TEXTURE_1D 136 
#define  WINED3D_SHADER_RESOURCE_TEXTURE_1DARRAY 135 
#define  WINED3D_SHADER_RESOURCE_TEXTURE_2D 134 
#define  WINED3D_SHADER_RESOURCE_TEXTURE_2DARRAY 133 
#define  WINED3D_SHADER_RESOURCE_TEXTURE_2DMS 132 
#define  WINED3D_SHADER_RESOURCE_TEXTURE_2DMSARRAY 131 
#define  WINED3D_SHADER_RESOURCE_TEXTURE_3D 130 
#define  WINED3D_SHADER_RESOURCE_TEXTURE_CUBE 129 
#define  WINED3D_SHADER_RESOURCE_TEXTURE_CUBEARRAY 128 
 scalar_t__ WINED3D_SHADER_TYPE_PIXEL ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 
 int /*<<< orphan*/  shader_dump_uav_flags (struct wined3d_string_buffer*,unsigned int) ; 

__attribute__((used)) static void shader_dump_decl_usage(struct wined3d_string_buffer *buffer,
        const struct wined3d_shader_semantic *semantic, unsigned int flags,
        const struct wined3d_shader_version *shader_version)
{
    shader_addline(buffer, "dcl");

    if (semantic->reg.reg.type == WINED3DSPR_SAMPLER)
    {
        switch (semantic->resource_type)
        {
            case WINED3D_SHADER_RESOURCE_TEXTURE_2D:
                shader_addline(buffer, "_2d");
                break;

            case WINED3D_SHADER_RESOURCE_TEXTURE_3D:
                shader_addline(buffer, "_3d");
                break;

            case WINED3D_SHADER_RESOURCE_TEXTURE_CUBE:
                shader_addline(buffer, "_cube");
                break;

            default:
                shader_addline(buffer, "_unknown_resource_type(%#x)", semantic->resource_type);
                break;
        }
    }
    else if (semantic->reg.reg.type == WINED3DSPR_RESOURCE || semantic->reg.reg.type == WINED3DSPR_UAV)
    {
        if (semantic->reg.reg.type == WINED3DSPR_RESOURCE)
            shader_addline(buffer, "_resource_");
        else
            shader_addline(buffer, "_uav_");
        switch (semantic->resource_type)
        {
            case WINED3D_SHADER_RESOURCE_BUFFER:
                shader_addline(buffer, "buffer");
                break;

            case WINED3D_SHADER_RESOURCE_TEXTURE_1D:
                shader_addline(buffer, "texture1d");
                break;

            case WINED3D_SHADER_RESOURCE_TEXTURE_2D:
                shader_addline(buffer, "texture2d");
                break;

            case WINED3D_SHADER_RESOURCE_TEXTURE_2DMS:
                shader_addline(buffer, "texture2dms");
                break;

            case WINED3D_SHADER_RESOURCE_TEXTURE_3D:
                shader_addline(buffer, "texture3d");
                break;

            case WINED3D_SHADER_RESOURCE_TEXTURE_CUBE:
                shader_addline(buffer, "texturecube");
                break;

            case WINED3D_SHADER_RESOURCE_TEXTURE_1DARRAY:
                shader_addline(buffer, "texture1darray");
                break;

            case WINED3D_SHADER_RESOURCE_TEXTURE_2DARRAY:
                shader_addline(buffer, "texture2darray");
                break;

            case WINED3D_SHADER_RESOURCE_TEXTURE_2DMSARRAY:
                shader_addline(buffer, "texture2dmsarray");
                break;

            case WINED3D_SHADER_RESOURCE_TEXTURE_CUBEARRAY:
                shader_addline(buffer, "texturecubearray");
                break;

            default:
                shader_addline(buffer, "unknown");
                break;
        }
        if (semantic->reg.reg.type == WINED3DSPR_UAV)
            shader_dump_uav_flags(buffer, flags);
        switch (semantic->resource_data_type)
        {
            case WINED3D_DATA_FLOAT:
                shader_addline(buffer, " (float)");
                break;

            case WINED3D_DATA_INT:
                shader_addline(buffer, " (int)");
                break;

            case WINED3D_DATA_UINT:
                shader_addline(buffer, " (uint)");
                break;

            case WINED3D_DATA_UNORM:
                shader_addline(buffer, " (unorm)");
                break;

            case WINED3D_DATA_SNORM:
                shader_addline(buffer, " (snorm)");
                break;

            default:
                shader_addline(buffer, " (unknown)");
                break;
        }
    }
    else
    {
        /* Pixel shaders 3.0 don't have usage semantics. */
        if (shader_version->major < 3 && shader_version->type == WINED3D_SHADER_TYPE_PIXEL)
            return;
        else
            shader_addline(buffer, "_");

        switch (semantic->usage)
        {
            case WINED3D_DECL_USAGE_POSITION:
                shader_addline(buffer, "position%u", semantic->usage_idx);
                break;

            case WINED3D_DECL_USAGE_BLEND_INDICES:
                shader_addline(buffer, "blend");
                break;

            case WINED3D_DECL_USAGE_BLEND_WEIGHT:
                shader_addline(buffer, "weight");
                break;

            case WINED3D_DECL_USAGE_NORMAL:
                shader_addline(buffer, "normal%u", semantic->usage_idx);
                break;

            case WINED3D_DECL_USAGE_PSIZE:
                shader_addline(buffer, "psize");
                break;

            case WINED3D_DECL_USAGE_COLOR:
                if (!semantic->usage_idx)
                    shader_addline(buffer, "color");
                else
                    shader_addline(buffer, "specular%u", (semantic->usage_idx - 1));
                break;

            case WINED3D_DECL_USAGE_TEXCOORD:
                shader_addline(buffer, "texture%u", semantic->usage_idx);
                break;

            case WINED3D_DECL_USAGE_TANGENT:
                shader_addline(buffer, "tangent");
                break;

            case WINED3D_DECL_USAGE_BINORMAL:
                shader_addline(buffer, "binormal");
                break;

            case WINED3D_DECL_USAGE_TESS_FACTOR:
                shader_addline(buffer, "tessfactor");
                break;

            case WINED3D_DECL_USAGE_POSITIONT:
                shader_addline(buffer, "positionT%u", semantic->usage_idx);
                break;

            case WINED3D_DECL_USAGE_FOG:
                shader_addline(buffer, "fog");
                break;

            case WINED3D_DECL_USAGE_DEPTH:
                shader_addline(buffer, "depth");
                break;

            case WINED3D_DECL_USAGE_SAMPLE:
                shader_addline(buffer, "sample");
                break;

            default:
                shader_addline(buffer, "<unknown_semantic(%#x)>", semantic->usage);
                FIXME("Unrecognised semantic usage %#x.\n", semantic->usage);
        }
    }
}