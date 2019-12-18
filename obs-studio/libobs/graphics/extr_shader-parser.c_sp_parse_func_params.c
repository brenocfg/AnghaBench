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
struct shader_var {int dummy; } ;
struct shader_parser {int /*<<< orphan*/  cfp; } ;
struct shader_func {int /*<<< orphan*/  params; } ;
struct TYPE_2__ {char* array; } ;
struct cf_token {TYPE_1__ str; } ;

/* Variables and functions */
 int PARSE_CONTINUE ; 
 int PARSE_EOF ; 
 int PARSE_SUCCESS ; 
 int /*<<< orphan*/  cf_adderror_syntax_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cf_next_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cf_peek_valid_token (int /*<<< orphan*/ *,struct cf_token*) ; 
 int /*<<< orphan*/  cf_token_clear (struct cf_token*) ; 
 int /*<<< orphan*/  cf_token_is (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,struct shader_var*) ; 
 int /*<<< orphan*/  shader_var_free (struct shader_var*) ; 
 int /*<<< orphan*/  shader_var_init (struct shader_var*) ; 
 int sp_parse_func_param (struct shader_parser*,struct shader_var*) ; 

__attribute__((used)) static bool sp_parse_func_params(struct shader_parser *sp,
				 struct shader_func *func)
{
	struct cf_token peek;
	int code;

	cf_token_clear(&peek);

	if (!cf_peek_valid_token(&sp->cfp, &peek))
		return false;

	if (*peek.str.array == ')') {
		cf_next_token(&sp->cfp);
		goto exit;
	}

	do {
		struct shader_var var;
		shader_var_init(&var);

		if (!cf_token_is(&sp->cfp, "(") && !cf_token_is(&sp->cfp, ","))
			cf_adderror_syntax_error(&sp->cfp);

		code = sp_parse_func_param(sp, &var);
		if (code != PARSE_SUCCESS) {
			shader_var_free(&var);

			if (code == PARSE_CONTINUE)
				goto exit;
			else if (code == PARSE_EOF)
				return false;
		}

		da_push_back(func->params, &var);
	} while (!cf_token_is(&sp->cfp, ")"));

exit:
	return true;
}