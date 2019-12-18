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
struct gl_shader_parser {int /*<<< orphan*/  parser; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  bfree (char*) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,char*) ; 
 int gl_shader_buildstring (struct gl_shader_parser*) ; 
 int shader_parse (int /*<<< orphan*/ *,char const*,char const*) ; 
 char* shader_parser_geterrors (int /*<<< orphan*/ *) ; 

bool gl_shader_parse(struct gl_shader_parser *glsp, const char *shader_str,
		     const char *file)
{
	bool success = shader_parse(&glsp->parser, shader_str, file);
	char *str = shader_parser_geterrors(&glsp->parser);
	if (str) {
		blog(LOG_WARNING, "Shader parser errors/warnings:\n%s\n", str);
		bfree(str);
	}

	if (success)
		success = gl_shader_buildstring(glsp);

	return success;
}