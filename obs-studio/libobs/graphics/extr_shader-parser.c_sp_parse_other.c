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
struct shader_parser {int /*<<< orphan*/  cfp; } ;

/* Variables and functions */
 scalar_t__ PARSE_SUCCESS ; 
 int /*<<< orphan*/  bfree (char*) ; 
 scalar_t__ cf_get_name (int /*<<< orphan*/ *,char**,char*,char*) ; 
 scalar_t__ cf_next_name (int /*<<< orphan*/ *,char**,char*,char*) ; 
 int /*<<< orphan*/  cf_next_valid_token (int /*<<< orphan*/ *) ; 
 scalar_t__ cf_token_is (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  report_invalid_func_keyword (struct shader_parser*,char*,int) ; 
 int /*<<< orphan*/  sp_get_var_specifiers (struct shader_parser*,int*,int*) ; 
 int /*<<< orphan*/  sp_parse_function (struct shader_parser*,char*,char*) ; 
 int /*<<< orphan*/  sp_parse_param (struct shader_parser*,char*,char*,int,int) ; 

__attribute__((used)) static void sp_parse_other(struct shader_parser *sp)
{
	bool is_const = false, is_uniform = false;
	char *type = NULL, *name = NULL;

	if (!sp_get_var_specifiers(sp, &is_const, &is_uniform))
		goto error;

	if (cf_get_name(&sp->cfp, &type, "type", ";") != PARSE_SUCCESS)
		goto error;
	if (cf_next_name(&sp->cfp, &name, "name", ";") != PARSE_SUCCESS)
		goto error;

	if (!cf_next_valid_token(&sp->cfp))
		goto error;

	if (cf_token_is(&sp->cfp, "(")) {
		report_invalid_func_keyword(sp, "const", is_const);
		report_invalid_func_keyword(sp, "uniform", is_uniform);

		sp_parse_function(sp, type, name);
		return;
	} else {
		sp_parse_param(sp, type, name, is_const, is_uniform);
		return;
	}

error:
	bfree(type);
	bfree(name);
}