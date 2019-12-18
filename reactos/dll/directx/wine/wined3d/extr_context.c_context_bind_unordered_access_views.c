#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ level_idx; } ;
struct TYPE_13__ {TYPE_4__ texture; } ;
struct TYPE_14__ {TYPE_5__ u; } ;
struct TYPE_11__ {scalar_t__ name; } ;
struct wined3d_unordered_access_view {scalar_t__ counter_bo; TYPE_7__* format; TYPE_6__ desc; TYPE_8__* resource; TYPE_3__ gl_view; } ;
struct wined3d_texture {int dummy; } ;
struct TYPE_10__ {TYPE_1__* uav_resource_info; } ;
struct wined3d_shader {TYPE_2__ reg_maps; } ;
struct wined3d_gl_info {int dummy; } ;
struct wined3d_context {struct wined3d_gl_info* gl_info; } ;
struct TYPE_16__ {scalar_t__ type; } ;
struct TYPE_15__ {int /*<<< orphan*/  glInternal; } ;
struct TYPE_9__ {scalar_t__ type; } ;
typedef  scalar_t__ GLuint ;
typedef  scalar_t__ GLint ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  GL_ATOMIC_COUNTER_BUFFER ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_R8 ; 
 int /*<<< orphan*/  GL_READ_WRITE ; 
 int /*<<< orphan*/  GL_TRUE ; 
 unsigned int MAX_UNORDERED_ACCESS_VIEWS ; 
 int /*<<< orphan*/  WARN (char*,unsigned int) ; 
 scalar_t__ WINED3D_RTYPE_BUFFER ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  glBindBufferBase (int /*<<< orphan*/ ,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  glBindImageTexture (unsigned int,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wined3d_texture* texture_from_resource (TYPE_8__*) ; 
 scalar_t__ wined3d_texture_get_texture_name (struct wined3d_texture*,struct wined3d_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void context_bind_unordered_access_views(struct wined3d_context *context,
        const struct wined3d_shader *shader, struct wined3d_unordered_access_view * const *views)
{
    const struct wined3d_gl_info *gl_info = context->gl_info;
    struct wined3d_unordered_access_view *view;
    GLuint texture_name;
    unsigned int i;
    GLint level;

    if (!shader)
        return;

    for (i = 0; i < MAX_UNORDERED_ACCESS_VIEWS; ++i)
    {
        if (!(view = views[i]))
        {
            if (shader->reg_maps.uav_resource_info[i].type)
                WARN("No unordered access view bound at index %u.\n", i);
            GL_EXTCALL(glBindImageTexture(i, 0, 0, GL_FALSE, 0, GL_READ_WRITE, GL_R8));
            continue;
        }

        if (view->gl_view.name)
        {
            texture_name = view->gl_view.name;
            level = 0;
        }
        else if (view->resource->type != WINED3D_RTYPE_BUFFER)
        {
            struct wined3d_texture *texture = texture_from_resource(view->resource);
            texture_name = wined3d_texture_get_texture_name(texture, context, FALSE);
            level = view->desc.u.texture.level_idx;
        }
        else
        {
            FIXME("Unsupported buffer unordered access view.\n");
            GL_EXTCALL(glBindImageTexture(i, 0, 0, GL_FALSE, 0, GL_READ_WRITE, GL_R8));
            continue;
        }

        GL_EXTCALL(glBindImageTexture(i, texture_name, level, GL_TRUE, 0, GL_READ_WRITE,
                view->format->glInternal));

        if (view->counter_bo)
            GL_EXTCALL(glBindBufferBase(GL_ATOMIC_COUNTER_BUFFER, i, view->counter_bo));
    }
    checkGLcall("Bind unordered access views");
}