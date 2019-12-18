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
struct gs_shader {int type; int /*<<< orphan*/ * device; } ;
struct gl_shader_parser {int dummy; } ;
typedef  int /*<<< orphan*/  gs_device_t ;
typedef  enum gs_shader_type { ____Placeholder_gs_shader_type } gs_shader_type ;

/* Variables and functions */
 struct gs_shader* bzalloc (int) ; 
 int gl_shader_init (struct gs_shader*,struct gl_shader_parser*,char const*,char**) ; 
 int /*<<< orphan*/  gl_shader_parse (struct gl_shader_parser*,char const*,char const*) ; 
 int /*<<< orphan*/  gl_shader_parser_free (struct gl_shader_parser*) ; 
 int /*<<< orphan*/  gl_shader_parser_init (struct gl_shader_parser*,int) ; 
 int /*<<< orphan*/  gs_shader_destroy (struct gs_shader*) ; 

__attribute__((used)) static struct gs_shader *shader_create(gs_device_t *device,
				       enum gs_shader_type type,
				       const char *shader_str, const char *file,
				       char **error_string)
{
	struct gs_shader *shader = bzalloc(sizeof(struct gs_shader));
	struct gl_shader_parser glsp;
	bool success = true;

	shader->device = device;
	shader->type = type;

	gl_shader_parser_init(&glsp, type);
	if (!gl_shader_parse(&glsp, shader_str, file))
		success = false;
	else
		success = gl_shader_init(shader, &glsp, file, error_string);

	if (!success) {
		gs_shader_destroy(shader);
		shader = NULL;
	}

	gl_shader_parser_free(&glsp);
	return shader;
}