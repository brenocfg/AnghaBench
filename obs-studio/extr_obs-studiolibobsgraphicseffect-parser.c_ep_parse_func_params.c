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
struct ep_var {int dummy; } ;
struct ep_func {int /*<<< orphan*/  param_vars; } ;
struct effect_parser {int /*<<< orphan*/  cfp; } ;
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
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,struct ep_var*) ; 
 int ep_parse_func_param (struct effect_parser*,struct ep_func*,struct ep_var*) ; 
 int /*<<< orphan*/  ep_var_free (struct ep_var*) ; 
 int /*<<< orphan*/  ep_var_init (struct ep_var*) ; 

__attribute__((used)) static bool ep_parse_func_params(struct effect_parser *ep, struct ep_func *func)
{
	struct cf_token peek;
	int code;

	cf_token_clear(&peek);

	if (!cf_peek_valid_token(&ep->cfp, &peek))
		return false;

	if (*peek.str.array == ')') {
		cf_next_token(&ep->cfp);
		goto exit;
	}

	do {
		struct ep_var var;
		ep_var_init(&var);

		if (!cf_token_is(&ep->cfp, "(") && !cf_token_is(&ep->cfp, ","))
			cf_adderror_syntax_error(&ep->cfp);

		code = ep_parse_func_param(ep, func, &var);
		if (code != PARSE_SUCCESS) {
			ep_var_free(&var);

			if (code == PARSE_CONTINUE)
				goto exit;
			else if (code == PARSE_EOF)
				return false;
		}

		da_push_back(func->param_vars, &var);
	} while (!cf_token_is(&ep->cfp, ")"));

exit:
	return true;
}