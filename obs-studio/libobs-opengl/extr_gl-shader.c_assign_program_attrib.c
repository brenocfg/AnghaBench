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
struct shader_attrib {int /*<<< orphan*/  name; } ;
struct gs_program {int /*<<< orphan*/  attribs; int /*<<< orphan*/  obj; } ;
typedef  int GLint ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,int*) ; 
 int glGetAttribLocation (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_success (char*) ; 

__attribute__((used)) static bool assign_program_attrib(struct gs_program *program,
				  struct shader_attrib *attrib)
{
	GLint attrib_obj = glGetAttribLocation(program->obj, attrib->name);
	if (!gl_success("glGetAttribLocation"))
		return false;

	if (attrib_obj == -1) {
		blog(LOG_ERROR,
		     "glGetAttribLocation: Could not find "
		     "attribute '%s'",
		     attrib->name);
		return false;
	}

	da_push_back(program->attribs, &attrib_obj);
	return true;
}