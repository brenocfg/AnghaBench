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
struct ra_d3d11 {int fl; } ;
struct ra {struct ra_d3d11* priv; } ;
typedef  enum glsl_shader { ____Placeholder_glsl_shader } glsl_shader ;

/* Variables and functions */
#define  D3D_FEATURE_LEVEL_10_0 135 
#define  D3D_FEATURE_LEVEL_10_1 134 
#define  D3D_FEATURE_LEVEL_9_1 133 
#define  D3D_FEATURE_LEVEL_9_2 132 
#define  D3D_FEATURE_LEVEL_9_3 131 
#define  GLSL_SHADER_COMPUTE 130 
#define  GLSL_SHADER_FRAGMENT 129 
#define  GLSL_SHADER_VERTEX 128 

__attribute__((used)) static const char *get_shader_target(struct ra *ra, enum glsl_shader type)
{
    struct ra_d3d11 *p = ra->priv;
    switch (p->fl) {
    default:
        switch (type) {
        case GLSL_SHADER_VERTEX:   return "vs_5_0";
        case GLSL_SHADER_FRAGMENT: return "ps_5_0";
        case GLSL_SHADER_COMPUTE:  return "cs_5_0";
        }
        break;
    case D3D_FEATURE_LEVEL_10_1:
        switch (type) {
        case GLSL_SHADER_VERTEX:   return "vs_4_1";
        case GLSL_SHADER_FRAGMENT: return "ps_4_1";
        case GLSL_SHADER_COMPUTE:  return "cs_4_1";
        }
        break;
    case D3D_FEATURE_LEVEL_10_0:
        switch (type) {
        case GLSL_SHADER_VERTEX:   return "vs_4_0";
        case GLSL_SHADER_FRAGMENT: return "ps_4_0";
        case GLSL_SHADER_COMPUTE:  return "cs_4_0";
        }
        break;
    case D3D_FEATURE_LEVEL_9_3:
        switch (type) {
        case GLSL_SHADER_VERTEX:   return "vs_4_0_level_9_3";
        case GLSL_SHADER_FRAGMENT: return "ps_4_0_level_9_3";
        }
        break;
    case D3D_FEATURE_LEVEL_9_2:
    case D3D_FEATURE_LEVEL_9_1:
        switch (type) {
        case GLSL_SHADER_VERTEX:   return "vs_4_0_level_9_1";
        case GLSL_SHADER_FRAGMENT: return "ps_4_0_level_9_1";
        }
        break;
    }
    return NULL;
}