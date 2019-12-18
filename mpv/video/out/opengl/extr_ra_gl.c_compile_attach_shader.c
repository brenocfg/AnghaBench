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
struct TYPE_3__ {int /*<<< orphan*/  (* DeleteShader ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* AttachShader ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* GetTranslatedShaderSourceANGLE ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,char const*) ;int /*<<< orphan*/  (* GetShaderiv ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* GetShaderInfoLog ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,char const*) ;int /*<<< orphan*/  (* CompileShader ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* ShaderSource ) (int /*<<< orphan*/ ,int,char const**,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* CreateShader ) (int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int GLint ;
typedef  int /*<<< orphan*/  GLenum ;
typedef  char const GLchar ;
typedef  TYPE_1__ GL ;

/* Variables and functions */
 int /*<<< orphan*/  GL_COMPILE_STATUS ; 
 int /*<<< orphan*/  GL_INFO_LOG_LENGTH ; 
 int /*<<< orphan*/  GL_TRANSLATED_SHADER_SOURCE_LENGTH_ANGLE ; 
 int /*<<< orphan*/  MP_DBG (struct ra*,char*) ; 
 int /*<<< orphan*/  MP_MSG (struct ra*,int,char*,char const*,...) ; 
 int MSGL_DEBUG ; 
 int MSGL_ERR ; 
 int MSGL_V ; 
 int /*<<< orphan*/  mp_log_source (int /*<<< orphan*/ ,int,char const*) ; 
 scalar_t__ mp_msg_test (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* ra_gl_get (struct ra*) ; 
 char* shader_typestr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (char const*) ; 
 char* talloc_zero_size (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void compile_attach_shader(struct ra *ra, GLuint program,
                                  GLenum type, const char *source, bool *ok)
{
    GL *gl = ra_gl_get(ra);

    GLuint shader = gl->CreateShader(type);
    gl->ShaderSource(shader, 1, &source, NULL);
    gl->CompileShader(shader);
    GLint status = 0;
    gl->GetShaderiv(shader, GL_COMPILE_STATUS, &status);
    GLint log_length = 0;
    gl->GetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);

    int pri = status ? (log_length > 1 ? MSGL_V : MSGL_DEBUG) : MSGL_ERR;
    const char *typestr = shader_typestr(type);
    if (mp_msg_test(ra->log, pri)) {
        MP_MSG(ra, pri, "%s shader source:\n", typestr);
        mp_log_source(ra->log, pri, source);
    }
    if (log_length > 1) {
        GLchar *logstr = talloc_zero_size(NULL, log_length + 1);
        gl->GetShaderInfoLog(shader, log_length, NULL, logstr);
        MP_MSG(ra, pri, "%s shader compile log (status=%d):\n%s\n",
               typestr, status, logstr);
        talloc_free(logstr);
    }
    if (gl->GetTranslatedShaderSourceANGLE && mp_msg_test(ra->log, MSGL_DEBUG)) {
        GLint len = 0;
        gl->GetShaderiv(shader, GL_TRANSLATED_SHADER_SOURCE_LENGTH_ANGLE, &len);
        if (len > 0) {
            GLchar *sstr = talloc_zero_size(NULL, len + 1);
            gl->GetTranslatedShaderSourceANGLE(shader, len, NULL, sstr);
            MP_DBG(ra, "Translated shader:\n");
            mp_log_source(ra->log, MSGL_DEBUG, sstr);
        }
    }

    gl->AttachShader(program, shader);
    gl->DeleteShader(shader);

    *ok &= status;
}