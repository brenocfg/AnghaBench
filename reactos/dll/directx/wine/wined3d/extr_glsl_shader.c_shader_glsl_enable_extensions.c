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
struct wined3d_string_buffer {int dummy; } ;
struct wined3d_gl_info {scalar_t__* supported; } ;

/* Variables and functions */
 size_t ARB_CULL_DISTANCE ; 
 size_t ARB_GPU_SHADER5 ; 
 size_t ARB_SHADER_ATOMIC_COUNTERS ; 
 size_t ARB_SHADER_BIT_ENCODING ; 
 size_t ARB_SHADER_IMAGE_LOAD_STORE ; 
 size_t ARB_SHADER_IMAGE_SIZE ; 
 size_t ARB_SHADER_STORAGE_BUFFER_OBJECT ; 
 size_t ARB_SHADING_LANGUAGE_420PACK ; 
 size_t ARB_SHADING_LANGUAGE_PACKING ; 
 size_t ARB_TEXTURE_CUBE_MAP_ARRAY ; 
 size_t ARB_TEXTURE_GATHER ; 
 size_t ARB_TEXTURE_QUERY_LEVELS ; 
 size_t ARB_UNIFORM_BUFFER_OBJECT ; 
 size_t EXT_GPU_SHADER4 ; 
 size_t EXT_TEXTURE_ARRAY ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*) ; 

__attribute__((used)) static void shader_glsl_enable_extensions(struct wined3d_string_buffer *buffer,
        const struct wined3d_gl_info *gl_info)
{
    if (gl_info->supported[ARB_CULL_DISTANCE])
        shader_addline(buffer, "#extension GL_ARB_cull_distance : enable\n");
    if (gl_info->supported[ARB_GPU_SHADER5])
        shader_addline(buffer, "#extension GL_ARB_gpu_shader5 : enable\n");
    if (gl_info->supported[ARB_SHADER_ATOMIC_COUNTERS])
        shader_addline(buffer, "#extension GL_ARB_shader_atomic_counters : enable\n");
    if (gl_info->supported[ARB_SHADER_BIT_ENCODING])
        shader_addline(buffer, "#extension GL_ARB_shader_bit_encoding : enable\n");
    if (gl_info->supported[ARB_SHADER_IMAGE_LOAD_STORE])
        shader_addline(buffer, "#extension GL_ARB_shader_image_load_store : enable\n");
    if (gl_info->supported[ARB_SHADER_IMAGE_SIZE])
        shader_addline(buffer, "#extension GL_ARB_shader_image_size : enable\n");
    if (gl_info->supported[ARB_SHADER_STORAGE_BUFFER_OBJECT])
        shader_addline(buffer, "#extension GL_ARB_shader_storage_buffer_object : enable\n");
    if (gl_info->supported[ARB_SHADING_LANGUAGE_420PACK])
        shader_addline(buffer, "#extension GL_ARB_shading_language_420pack : enable\n");
    if (gl_info->supported[ARB_SHADING_LANGUAGE_PACKING])
        shader_addline(buffer, "#extension GL_ARB_shading_language_packing : enable\n");
    if (gl_info->supported[ARB_TEXTURE_CUBE_MAP_ARRAY])
        shader_addline(buffer, "#extension GL_ARB_texture_cube_map_array : enable\n");
    if (gl_info->supported[ARB_TEXTURE_GATHER])
        shader_addline(buffer, "#extension GL_ARB_texture_gather : enable\n");
    if (gl_info->supported[ARB_TEXTURE_QUERY_LEVELS])
        shader_addline(buffer, "#extension GL_ARB_texture_query_levels : enable\n");
    if (gl_info->supported[ARB_UNIFORM_BUFFER_OBJECT])
        shader_addline(buffer, "#extension GL_ARB_uniform_buffer_object : enable\n");
    if (gl_info->supported[EXT_GPU_SHADER4])
        shader_addline(buffer, "#extension GL_EXT_gpu_shader4 : enable\n");
    if (gl_info->supported[EXT_TEXTURE_ARRAY])
        shader_addline(buffer, "#extension GL_EXT_texture_array : enable\n");
}