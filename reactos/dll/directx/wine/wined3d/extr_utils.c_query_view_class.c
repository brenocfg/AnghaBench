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
struct wined3d_format {scalar_t__ gl_view_class; int /*<<< orphan*/  id; int /*<<< orphan*/  rtInternal; int /*<<< orphan*/  glGammaInternal; int /*<<< orphan*/  glInternal; } ;
typedef  scalar_t__ GLenum ;

/* Variables and functions */
 scalar_t__ GL_NONE ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  debug_d3dformat (int /*<<< orphan*/ ) ; 
 scalar_t__ lookup_gl_view_class (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void query_view_class(struct wined3d_format *format)
{
    GLenum internal_view_class, gamma_view_class, rt_view_class;

    internal_view_class = lookup_gl_view_class(format->glInternal);
    gamma_view_class = lookup_gl_view_class(format->glGammaInternal);
    rt_view_class = lookup_gl_view_class(format->rtInternal);

    if (internal_view_class == gamma_view_class || gamma_view_class == rt_view_class)
    {
        format->gl_view_class = internal_view_class;
        TRACE("Format %s is member of GL view class %#x.\n",
                debug_d3dformat(format->id), format->gl_view_class);
    }
    else
    {
        format->gl_view_class = GL_NONE;
    }
}