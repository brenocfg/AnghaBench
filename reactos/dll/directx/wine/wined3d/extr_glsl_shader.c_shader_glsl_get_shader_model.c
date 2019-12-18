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
struct wined3d_gl_info {scalar_t__ glsl_version; scalar_t__* supported; } ;
typedef  int BOOL ;

/* Variables and functions */
 size_t ARB_COMPUTE_SHADER ; 
 size_t ARB_CULL_DISTANCE ; 
 size_t ARB_DERIVATIVE_CONTROL ; 
 size_t ARB_DRAW_INDIRECT ; 
 size_t ARB_GPU_SHADER5 ; 
 size_t ARB_SAMPLER_OBJECTS ; 
 size_t ARB_SHADER_ATOMIC_COUNTERS ; 
 size_t ARB_SHADER_BIT_ENCODING ; 
 size_t ARB_SHADER_IMAGE_LOAD_STORE ; 
 size_t ARB_SHADER_IMAGE_SIZE ; 
 size_t ARB_SHADER_TEXTURE_LOD ; 
 size_t ARB_SHADING_LANGUAGE_PACKING ; 
 size_t ARB_TESSELLATION_SHADER ; 
 size_t ARB_TEXTURE_GATHER ; 
 size_t ARB_TEXTURE_SWIZZLE ; 
 size_t ARB_TRANSFORM_FEEDBACK3 ; 
 scalar_t__ MAKEDWORD_VERSION (int,int) ; 
 size_t WINED3D_GL_VERSION_3_2 ; 
 scalar_t__ shader_glsl_has_core_grad (struct wined3d_gl_info const*) ; 

__attribute__((used)) static unsigned int shader_glsl_get_shader_model(const struct wined3d_gl_info *gl_info)
{
    BOOL shader_model_4 = gl_info->glsl_version >= MAKEDWORD_VERSION(1, 50)
            && gl_info->supported[WINED3D_GL_VERSION_3_2]
            && gl_info->supported[ARB_SAMPLER_OBJECTS]
            && gl_info->supported[ARB_SHADER_BIT_ENCODING]
            && gl_info->supported[ARB_TEXTURE_SWIZZLE];

    if (shader_model_4
            && gl_info->supported[ARB_COMPUTE_SHADER]
            && gl_info->supported[ARB_CULL_DISTANCE]
            && gl_info->supported[ARB_DERIVATIVE_CONTROL]
            && gl_info->supported[ARB_DRAW_INDIRECT]
            && gl_info->supported[ARB_GPU_SHADER5]
            && gl_info->supported[ARB_SHADER_ATOMIC_COUNTERS]
            && gl_info->supported[ARB_SHADER_IMAGE_LOAD_STORE]
            && gl_info->supported[ARB_SHADER_IMAGE_SIZE]
            && gl_info->supported[ARB_SHADING_LANGUAGE_PACKING]
            && gl_info->supported[ARB_TESSELLATION_SHADER]
            && gl_info->supported[ARB_TEXTURE_GATHER]
            && gl_info->supported[ARB_TRANSFORM_FEEDBACK3])
        return 5;

    if (shader_model_4)
        return 4;

    /* Support for texldd and texldl instructions in pixel shaders is required
     * for SM3. */
    if (shader_glsl_has_core_grad(gl_info) || gl_info->supported[ARB_SHADER_TEXTURE_LOD])
        return 3;

    return 2;
}