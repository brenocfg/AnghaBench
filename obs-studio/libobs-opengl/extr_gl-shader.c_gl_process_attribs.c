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
struct gs_shader {int dummy; } ;
struct TYPE_2__ {size_t num; struct gl_parser_attrib* array; } ;
struct gl_shader_parser {TYPE_1__ attribs; } ;
struct gl_parser_attrib {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gl_process_attrib (struct gs_shader*,struct gl_parser_attrib*) ; 

__attribute__((used)) static inline bool gl_process_attribs(struct gs_shader *shader,
				      struct gl_shader_parser *glsp)
{
	size_t i;
	for (i = 0; i < glsp->attribs.num; i++) {
		struct gl_parser_attrib *pa = glsp->attribs.array + i;
		if (!gl_process_attrib(shader, pa))
			return false;
	}

	return true;
}