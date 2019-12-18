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
typedef  int /*<<< orphan*/  gs_shader_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  bfree (char*) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  gs_valid_p (char*,char const*) ; 
 int /*<<< orphan*/ * gs_vertexshader_create (char*,char const*,char**) ; 
 char* os_quick_read_utf8_file (char const*) ; 

gs_shader_t *gs_vertexshader_create_from_file(const char *file,
					      char **error_string)
{
	if (!gs_valid_p("gs_vertexshader_create_from_file", file))
		return NULL;

	char *file_string;
	gs_shader_t *shader = NULL;

	file_string = os_quick_read_utf8_file(file);
	if (!file_string) {
		blog(LOG_ERROR, "Could not load vertex shader file '%s'", file);
		return NULL;
	}

	shader = gs_vertexshader_create(file_string, file, error_string);
	bfree(file_string);

	return shader;
}