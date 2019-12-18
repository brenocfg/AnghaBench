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
struct shader_var {char* type; char* name; size_t gl_sampler_id; int /*<<< orphan*/  default_val; scalar_t__ array_count; int /*<<< orphan*/ * mapping; int /*<<< orphan*/  var_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHADER_VAR_CONST ; 
 int /*<<< orphan*/  SHADER_VAR_NONE ; 
 int /*<<< orphan*/  SHADER_VAR_UNIFORM ; 
 int /*<<< orphan*/  da_init (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void shader_var_init_param(struct shader_var *sv, char *type,
					 char *name, bool is_uniform,
					 bool is_const)
{
	if (is_uniform)
		sv->var_type = SHADER_VAR_UNIFORM;
	else if (is_const)
		sv->var_type = SHADER_VAR_CONST;
	else
		sv->var_type = SHADER_VAR_NONE;

	sv->type = type;
	sv->name = name;
	sv->mapping = NULL;
	sv->array_count = 0;
	sv->gl_sampler_id = (size_t)-1;
	da_init(sv->default_val);
}