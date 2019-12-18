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
struct wined3d_gl_info {int quirks; } ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int,...) ; 
 int /*<<< orphan*/  FIXME_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_INFO_LOG_LENGTH ; 
 int /*<<< orphan*/  WARN (char*,int,...) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int WINED3D_QUIRK_INFO_LOG_SPAM ; 
 int /*<<< orphan*/  d3d_shader ; 
 char* get_info_log_line (char const**) ; 
 int /*<<< orphan*/  glGetProgramInfoLog (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  glGetProgramiv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  glGetShaderInfoLog (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  glGetShaderiv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 char* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (char*) ; 

void print_glsl_info_log(const struct wined3d_gl_info *gl_info, GLuint id, BOOL program)
{
    int length = 0;
    char *log;

    if (!WARN_ON(d3d_shader) && !FIXME_ON(d3d_shader))
        return;

    if (program)
        GL_EXTCALL(glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length));
    else
        GL_EXTCALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));

    /* A size of 1 is just a null-terminated string, so the log should be bigger than
     * that if there are errors. */
    if (length > 1)
    {
        const char *ptr, *line;

        log = heap_alloc(length);
        /* The info log is supposed to be zero-terminated, but at least some
         * versions of fglrx don't terminate the string properly. The reported
         * length does include the terminator, so explicitly set it to zero
         * here. */
        log[length - 1] = 0;
        if (program)
            GL_EXTCALL(glGetProgramInfoLog(id, length, NULL, log));
        else
            GL_EXTCALL(glGetShaderInfoLog(id, length, NULL, log));

        ptr = log;
        if (gl_info->quirks & WINED3D_QUIRK_INFO_LOG_SPAM)
        {
            WARN("Info log received from GLSL shader #%u:\n", id);
            while ((line = get_info_log_line(&ptr))) WARN("    %.*s", (int)(ptr - line), line);
        }
        else
        {
            FIXME("Info log received from GLSL shader #%u:\n", id);
            while ((line = get_info_log_line(&ptr))) FIXME("    %.*s", (int)(ptr - line), line);
        }
        heap_free(log);
    }
}