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
struct TYPE_2__ {size_t num; scalar_t__ array; } ;
struct shader_func {TYPE_1__ params; } ;
struct gl_shader_parser {int /*<<< orphan*/  gl_string; } ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_cat (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gl_write_storage_var (struct gl_shader_parser*,scalar_t__,int,char*) ; 

__attribute__((used)) static inline void gl_write_inputs(struct gl_shader_parser *glsp,
				   struct shader_func *main)
{
	size_t i;
	for (i = 0; i < main->params.num; i++)
		gl_write_storage_var(glsp, main->params.array + i, true,
				     "inputval_");
	dstr_cat(&glsp->gl_string, "\n");
}