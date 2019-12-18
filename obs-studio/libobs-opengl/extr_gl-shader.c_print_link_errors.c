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
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,char*) ; 
 char* calloc (int,scalar_t__) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  glGetProgramInfoLog (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  glGetProgramiv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  gl_success (char*) ; 

__attribute__((used)) static void print_link_errors(GLuint program)
{
	char *errors = NULL;
	GLint info_len = 0;
	GLsizei chars_written = 0;

	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_len);
	if (!gl_success("glGetProgramiv") || !info_len)
		return;

	errors = calloc(1, info_len + 1);
	glGetProgramInfoLog(program, info_len, &chars_written, errors);
	gl_success("glGetShaderInfoLog");

	blog(LOG_DEBUG, "Linker warnings/errors:\n%s", errors);

	free(errors);
}