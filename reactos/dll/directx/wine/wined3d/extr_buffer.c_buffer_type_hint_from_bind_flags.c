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
struct wined3d_gl_info {scalar_t__* supported; } ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 size_t ARB_TEXTURE_BUFFER_OBJECT ; 
 int /*<<< orphan*/  FIXME (char*,unsigned int) ; 
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_ELEMENT_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_TEXTURE_BUFFER ; 
 int /*<<< orphan*/  GL_TRANSFORM_FEEDBACK_BUFFER ; 
 int /*<<< orphan*/  GL_UNIFORM_BUFFER ; 
 unsigned int WINED3D_BIND_CONSTANT_BUFFER ; 
 unsigned int WINED3D_BIND_INDEX_BUFFER ; 
 unsigned int WINED3D_BIND_SHADER_RESOURCE ; 
 unsigned int WINED3D_BIND_STREAM_OUTPUT ; 
 unsigned int WINED3D_BIND_UNORDERED_ACCESS ; 
 unsigned int WINED3D_BIND_VERTEX_BUFFER ; 

__attribute__((used)) static GLenum buffer_type_hint_from_bind_flags(const struct wined3d_gl_info *gl_info,
        unsigned int bind_flags)
{
    if (bind_flags == WINED3D_BIND_INDEX_BUFFER)
        return GL_ELEMENT_ARRAY_BUFFER;

    if (bind_flags & (WINED3D_BIND_SHADER_RESOURCE | WINED3D_BIND_UNORDERED_ACCESS)
            && gl_info->supported[ARB_TEXTURE_BUFFER_OBJECT])
        return GL_TEXTURE_BUFFER;

    if (bind_flags & WINED3D_BIND_CONSTANT_BUFFER)
        return GL_UNIFORM_BUFFER;

    if (bind_flags & WINED3D_BIND_STREAM_OUTPUT)
        return GL_TRANSFORM_FEEDBACK_BUFFER;

    if (bind_flags & ~(WINED3D_BIND_VERTEX_BUFFER | WINED3D_BIND_INDEX_BUFFER))
        FIXME("Unhandled bind flags %#x.\n", bind_flags);

    return GL_ARRAY_BUFFER;
}