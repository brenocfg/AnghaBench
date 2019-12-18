#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gs_shader {scalar_t__ type; int /*<<< orphan*/  obj; } ;
struct TYPE_2__ {char* array; } ;
struct gl_shader_parser {TYPE_1__ gl_string; } ;
typedef  int /*<<< orphan*/  GLsizei ;
typedef  int GLint ;
typedef  int /*<<< orphan*/  GLenum ;
typedef  int /*<<< orphan*/  GLchar ;

/* Variables and functions */
 int /*<<< orphan*/  GL_COMPILE_STATUS ; 
 int /*<<< orphan*/  GL_INFO_LOG_LENGTH ; 
 scalar_t__ GS_SHADER_VERTEX ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  convert_shader_type (scalar_t__) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  glCompileShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glCreateShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGetShaderInfoLog (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  glGetShaderiv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  glShaderSource (int /*<<< orphan*/ ,int,int /*<<< orphan*/  const**,int /*<<< orphan*/ ) ; 
 int gl_add_params (struct gs_shader*,struct gl_shader_parser*) ; 
 int /*<<< orphan*/  gl_add_samplers (struct gs_shader*,struct gl_shader_parser*) ; 
 int /*<<< orphan*/  gl_get_shader_info (int /*<<< orphan*/ ,char const*,char**) ; 
 int gl_process_attribs (struct gs_shader*,struct gl_shader_parser*) ; 
 int /*<<< orphan*/  gl_success (char*) ; 
 char* malloc (int) ; 

__attribute__((used)) static bool gl_shader_init(struct gs_shader *shader,
			   struct gl_shader_parser *glsp, const char *file,
			   char **error_string)
{
	GLenum type = convert_shader_type(shader->type);
	int compiled = 0;
	bool success = true;

	shader->obj = glCreateShader(type);
	if (!gl_success("glCreateShader") || !shader->obj)
		return false;

	glShaderSource(shader->obj, 1, (const GLchar **)&glsp->gl_string.array,
		       0);
	if (!gl_success("glShaderSource"))
		return false;

	glCompileShader(shader->obj);
	if (!gl_success("glCompileShader"))
		return false;

#if 0
	blog(LOG_DEBUG, "+++++++++++++++++++++++++++++++++++");
	blog(LOG_DEBUG, "  GL shader string for: %s", file);
	blog(LOG_DEBUG, "-----------------------------------");
	blog(LOG_DEBUG, "%s", glsp->gl_string.array);
	blog(LOG_DEBUG, "+++++++++++++++++++++++++++++++++++");
#endif

	glGetShaderiv(shader->obj, GL_COMPILE_STATUS, &compiled);
	if (!gl_success("glGetShaderiv"))
		return false;

	if (!compiled) {
		GLint infoLength = 0;
		glGetShaderiv(shader->obj, GL_INFO_LOG_LENGTH, &infoLength);

		char *infoLog = malloc(sizeof(char) * infoLength);

		GLsizei returnedLength = 0;
		glGetShaderInfoLog(shader->obj, infoLength, &returnedLength,
				   infoLog);
		blog(LOG_ERROR, "Error compiling shader:\n%s\n", infoLog);

		free(infoLog);

		success = false;
	}

	gl_get_shader_info(shader->obj, file, error_string);

	if (success)
		success = gl_add_params(shader, glsp);
	/* Only vertex shaders actually require input attributes */
	if (success && shader->type == GS_SHADER_VERTEX)
		success = gl_process_attribs(shader, glsp);
	if (success)
		gl_add_samplers(shader, glsp);

	return success;
}