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
struct TYPE_3__ {int /*<<< orphan*/  (* p_glGetInternalformativ ) (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,scalar_t__*) ;} ;
struct TYPE_4__ {TYPE_1__ ext; } ;
struct wined3d_gl_info {TYPE_2__ gl_ops; } ;
struct wined3d_format {int /*<<< orphan*/ * flags; int /*<<< orphan*/  id; } ;
typedef  enum wined3d_gl_resource_type { ____Placeholder_wined3d_gl_resource_type } wined3d_gl_resource_type ;
typedef  scalar_t__ GLint ;
typedef  int /*<<< orphan*/  GLenum ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ GL_FULL_SUPPORT ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  debug_d3dformat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  wined3d_gl_type_to_enum (int) ; 

__attribute__((used)) static void query_format_flag(struct wined3d_gl_info *gl_info, struct wined3d_format *format,
        GLint internal, GLenum pname, DWORD flag, const char *string)
{
    GLint value;
    enum wined3d_gl_resource_type type;

    for (type = 0; type < ARRAY_SIZE(format->flags); ++type)
    {
        gl_info->gl_ops.ext.p_glGetInternalformativ(wined3d_gl_type_to_enum(type), internal, pname, 1, &value);
        if (value == GL_FULL_SUPPORT)
        {
            TRACE("Format %s supports %s, resource type %u.\n", debug_d3dformat(format->id), string, type);
            format->flags[type] |= flag;
        }
        else
        {
            TRACE("Format %s doesn't support %s, resource type %u.\n", debug_d3dformat(format->id), string, type);
            format->flags[type] &= ~flag;
        }
    }
}