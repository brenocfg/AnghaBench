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
struct TYPE_2__ {struct wined3d_format* format; } ;
struct wined3d_texture {unsigned int level_count; unsigned int layer_count; TYPE_1__ resource; } ;
struct wined3d_gl_info {int dummy; } ;
struct wined3d_format {int /*<<< orphan*/  glType; int /*<<< orphan*/  glFormat; int /*<<< orphan*/  glInternal; int /*<<< orphan*/  glGammaInternal; } ;
struct wined3d_context {struct wined3d_gl_info* gl_info; } ;
typedef  int /*<<< orphan*/  GLenum ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_TEXTURE_3D ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  glTexImage3D (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glTexStorage3D (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_texture_bind_and_dirtify (struct wined3d_texture*,struct wined3d_context*,scalar_t__) ; 
 int /*<<< orphan*/  wined3d_texture_get_level_depth (struct wined3d_texture*,unsigned int) ; 
 int /*<<< orphan*/  wined3d_texture_get_level_height (struct wined3d_texture*,unsigned int) ; 
 int /*<<< orphan*/  wined3d_texture_get_level_width (struct wined3d_texture*,unsigned int) ; 
 scalar_t__ wined3d_texture_use_immutable_storage (struct wined3d_texture*,struct wined3d_gl_info const*) ; 

__attribute__((used)) static void texture3d_prepare_texture(struct wined3d_texture *texture, struct wined3d_context *context, BOOL srgb)
{
    const struct wined3d_format *format = texture->resource.format;
    GLenum internal = srgb ? format->glGammaInternal : format->glInternal;
    unsigned int sub_count = texture->level_count * texture->layer_count;
    const struct wined3d_gl_info *gl_info = context->gl_info;
    unsigned int i;

    wined3d_texture_bind_and_dirtify(texture, context, srgb);

    if (wined3d_texture_use_immutable_storage(texture, gl_info))
    {
        GL_EXTCALL(glTexStorage3D(GL_TEXTURE_3D, texture->level_count, internal,
                wined3d_texture_get_level_width(texture, 0),
                wined3d_texture_get_level_height(texture, 0),
                wined3d_texture_get_level_depth(texture, 0)));
        checkGLcall("glTexStorage3D");
    }
    else
    {
        for (i = 0; i < sub_count; ++i)
        {
            GL_EXTCALL(glTexImage3D(GL_TEXTURE_3D, i, internal,
                    wined3d_texture_get_level_width(texture, i),
                    wined3d_texture_get_level_height(texture, i),
                    wined3d_texture_get_level_depth(texture, i),
                    0, format->glFormat, format->glType, NULL));
            checkGLcall("glTexImage3D");
        }
    }
}