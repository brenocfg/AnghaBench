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
struct wined3d_gl_info {int dummy; } ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  GLint ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_LINK_STATUS ; 
 int /*<<< orphan*/  TRACE_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  d3d_shader ; 
 int /*<<< orphan*/  glGetProgramiv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_glsl_info_log (struct wined3d_gl_info const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_dump_program_source (struct wined3d_gl_info const*,int /*<<< orphan*/ ) ; 

void shader_glsl_validate_link(const struct wined3d_gl_info *gl_info, GLuint program)
{
    GLint tmp;

    if (!TRACE_ON(d3d_shader) && !FIXME_ON(d3d_shader))
        return;

    GL_EXTCALL(glGetProgramiv(program, GL_LINK_STATUS, &tmp));
    if (!tmp)
    {
        FIXME("Program %u link status invalid.\n", program);
        shader_glsl_dump_program_source(gl_info, program);
    }

    print_glsl_info_log(gl_info, program, TRUE);
}