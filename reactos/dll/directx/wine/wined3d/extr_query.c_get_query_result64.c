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
typedef  int /*<<< orphan*/  UINT64 ;
typedef  int /*<<< orphan*/  GLuint64 ;
typedef  int /*<<< orphan*/  GLuint ;

/* Variables and functions */
 size_t ARB_TIMER_QUERY ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_QUERY_RESULT ; 
 int /*<<< orphan*/  glGetQueryObjectui64v (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glGetQueryObjectuiv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT64 get_query_result64(GLuint id, const struct wined3d_gl_info *gl_info)
{
    if (gl_info->supported[ARB_TIMER_QUERY])
    {
        GLuint64 result;
        GL_EXTCALL(glGetQueryObjectui64v(id, GL_QUERY_RESULT, &result));
        return result;
    }
    else
    {
        GLuint result;
        GL_EXTCALL(glGetQueryObjectuiv(id, GL_QUERY_RESULT, &result));
        return result;
    }
}