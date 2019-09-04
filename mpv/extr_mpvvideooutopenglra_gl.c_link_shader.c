#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ra {int /*<<< orphan*/  log; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* GetProgramInfoLog ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* GetProgramiv ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* LinkProgram ) (int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int GLint ;
typedef  int /*<<< orphan*/  GLchar ;
typedef  TYPE_1__ GL ;

/* Variables and functions */
 int /*<<< orphan*/  GL_INFO_LOG_LENGTH ; 
 int /*<<< orphan*/  GL_LINK_STATUS ; 
 int /*<<< orphan*/  MP_MSG (struct ra*,int,char*,int,int /*<<< orphan*/ *) ; 
 int MSGL_DEBUG ; 
 int MSGL_ERR ; 
 int MSGL_V ; 
 scalar_t__ mp_msg_test (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* ra_gl_get (struct ra*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * talloc_zero_size (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void link_shader(struct ra *ra, GLuint program, bool *ok)
{
    GL *gl = ra_gl_get(ra);

    gl->LinkProgram(program);
    GLint status = 0;
    gl->GetProgramiv(program, GL_LINK_STATUS, &status);
    GLint log_length = 0;
    gl->GetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);

    int pri = status ? (log_length > 1 ? MSGL_V : MSGL_DEBUG) : MSGL_ERR;
    if (mp_msg_test(ra->log, pri)) {
        GLchar *logstr = talloc_zero_size(NULL, log_length + 1);
        gl->GetProgramInfoLog(program, log_length, NULL, logstr);
        MP_MSG(ra, pri, "shader link log (status=%d): %s\n", status, logstr);
        talloc_free(logstr);
    }

    *ok &= status;
}