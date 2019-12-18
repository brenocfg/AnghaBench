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
struct shader_var {int dummy; } ;
struct shader_parser {int /*<<< orphan*/  params; int /*<<< orphan*/  cfp; } ;

/* Variables and functions */
 scalar_t__ cf_token_is (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,struct shader_var*) ; 
 int /*<<< orphan*/  shader_var_free (struct shader_var*) ; 
 int /*<<< orphan*/  shader_var_init_param (struct shader_var*,char*,char*,int,int) ; 
 int /*<<< orphan*/  sp_parse_param_array (struct shader_parser*,struct shader_var*) ; 
 int /*<<< orphan*/  sp_parse_param_assign (struct shader_parser*,struct shader_var*) ; 

__attribute__((used)) static void sp_parse_param(struct shader_parser *sp, char *type, char *name,
			   bool is_const, bool is_uniform)
{
	struct shader_var param;
	shader_var_init_param(&param, type, name, is_uniform, is_const);

	if (cf_token_is(&sp->cfp, ";"))
		goto complete;
	if (cf_token_is(&sp->cfp, "[") && !sp_parse_param_array(sp, &param))
		goto error;
	if (cf_token_is(&sp->cfp, "=") && !sp_parse_param_assign(sp, &param))
		goto error;
	if (!cf_token_is(&sp->cfp, ";"))
		goto error;

complete:
	da_push_back(sp->params, &param);
	return;

error:
	shader_var_free(&param);
}