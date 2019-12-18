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
struct macro_params {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  da; } ;
struct macro_param {TYPE_2__ tokens; } ;
struct TYPE_3__ {char* array; } ;
struct cf_token {scalar_t__ type; TYPE_1__ str; } ;
struct cf_preprocessor {int dummy; } ;

/* Variables and functions */
 scalar_t__ CFTOKEN_NONE ; 
 int /*<<< orphan*/  append_end_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  append_space (struct cf_preprocessor*,int /*<<< orphan*/ *,struct cf_token const*) ; 
 int /*<<< orphan*/  cf_adderror_unexpected_eof (struct cf_preprocessor*,struct cf_token*) ; 
 int /*<<< orphan*/  cf_preprocess_addtoken (struct cf_preprocessor*,int /*<<< orphan*/ *,struct cf_token**,struct cf_token const*,struct macro_params const*) ; 

__attribute__((used)) static void cf_preprocess_save_macro_param(
	struct cf_preprocessor *pp, struct cf_token **p_cur_token,
	struct macro_param *param, const struct cf_token *base,
	const struct macro_params *cur_params)
{
	struct cf_token *cur_token = *p_cur_token;
	int brace_count = 0;

	append_space(pp, &param->tokens.da, base);

	while (cur_token->type != CFTOKEN_NONE) {
		if (*cur_token->str.array == '(') {
			brace_count++;
		} else if (*cur_token->str.array == ')') {
			if (brace_count)
				brace_count--;
			else
				break;
		} else if (*cur_token->str.array == ',') {
			if (!brace_count)
				break;
		}

		cf_preprocess_addtoken(pp, &param->tokens.da, &cur_token, base,
				       cur_params);
	}

	if (cur_token->type == CFTOKEN_NONE)
		cf_adderror_unexpected_eof(pp, cur_token);

	append_space(pp, &param->tokens.da, base);
	append_end_token(&param->tokens.da);

	*p_cur_token = cur_token;
}