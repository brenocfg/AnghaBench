#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct shader_sampler {int dummy; } ;
struct gs_shader {int dummy; } ;
struct TYPE_3__ {size_t num; struct shader_sampler* array; } ;
struct TYPE_4__ {TYPE_1__ samplers; } ;
struct gl_shader_parser {TYPE_2__ parser; } ;

/* Variables and functions */
 int /*<<< orphan*/  gl_add_sampler (struct gs_shader*,struct shader_sampler*) ; 

__attribute__((used)) static inline void gl_add_samplers(struct gs_shader *shader,
				   struct gl_shader_parser *glsp)
{
	size_t i;
	for (i = 0; i < glsp->parser.samplers.num; i++) {
		struct shader_sampler *sampler =
			glsp->parser.samplers.array + i;
		gl_add_sampler(shader, sampler);
	}
}