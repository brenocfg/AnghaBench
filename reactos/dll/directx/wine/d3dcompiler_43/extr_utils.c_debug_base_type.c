#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hlsl_type {int base_type; int /*<<< orphan*/  sampler_dim; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
#define  HLSL_SAMPLER_DIM_1D 139 
#define  HLSL_SAMPLER_DIM_2D 138 
#define  HLSL_SAMPLER_DIM_3D 137 
#define  HLSL_SAMPLER_DIM_CUBE 136 
#define  HLSL_SAMPLER_DIM_GENERIC 135 
#define  HLSL_TYPE_BOOL 134 
#define  HLSL_TYPE_DOUBLE 133 
#define  HLSL_TYPE_FLOAT 132 
#define  HLSL_TYPE_HALF 131 
#define  HLSL_TYPE_INT 130 
#define  HLSL_TYPE_SAMPLER 129 
#define  HLSL_TYPE_UINT 128 

__attribute__((used)) static const char *debug_base_type(const struct hlsl_type *type)
{
    const char *name = "(unknown)";

    switch (type->base_type)
    {
        case HLSL_TYPE_FLOAT:        name = "float";         break;
        case HLSL_TYPE_HALF:         name = "half";          break;
        case HLSL_TYPE_DOUBLE:       name = "double";        break;
        case HLSL_TYPE_INT:          name = "int";           break;
        case HLSL_TYPE_UINT:         name = "uint";          break;
        case HLSL_TYPE_BOOL:         name = "bool";          break;
        case HLSL_TYPE_SAMPLER:
            switch (type->sampler_dim)
            {
                case HLSL_SAMPLER_DIM_GENERIC: name = "sampler";       break;
                case HLSL_SAMPLER_DIM_1D:      name = "sampler1D";     break;
                case HLSL_SAMPLER_DIM_2D:      name = "sampler2D";     break;
                case HLSL_SAMPLER_DIM_3D:      name = "sampler3D";     break;
                case HLSL_SAMPLER_DIM_CUBE:    name = "samplerCUBE";   break;
            }
            break;
        default:
            FIXME("Unhandled case %u\n", type->base_type);
    }
    return name;
}