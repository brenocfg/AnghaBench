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
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  GLsizei ;
typedef  scalar_t__ GLint ;

/* Variables and functions */
 int /*<<< orphan*/  GL_INFO_LOG_LENGTH ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  bfree (char*) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 char* bzalloc (scalar_t__) ; 
 int /*<<< orphan*/  glGetShaderInfoLog (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  glGetShaderiv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  gl_success (char*) ; 

__attribute__((used)) static void gl_get_shader_info(GLuint shader, const char *file,
			       char **error_string)
{
	char *errors;
	GLint info_len = 0;
	GLsizei chars_written = 0;

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_len);
	if (!gl_success("glGetProgramiv") || !info_len)
		return;

	errors = bzalloc(info_len + 1);
	glGetShaderInfoLog(shader, info_len, &chars_written, errors);
	gl_success("glGetShaderInfoLog");

	blog(LOG_DEBUG, "Compiler warnings/errors for %s:\n%s", file, errors);

	if (error_string)
		*error_string = errors;
	else
		bfree(errors);
}