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
struct macro_params {int dummy; } ;
struct macro_param {int dummy; } ;
struct darray {int dummy; } ;
struct cf_token {scalar_t__ type; int /*<<< orphan*/  str; } ;
struct cf_preprocessor {scalar_t__ ignore_state; } ;
struct cf_def {int dummy; } ;

/* Variables and functions */
 scalar_t__ CFTOKEN_NAME ; 
 struct cf_def* cf_preprocess_get_def (struct cf_preprocessor*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cf_preprocess_unwrap_define (struct cf_preprocessor*,struct darray*,struct cf_token**,struct cf_token const*,struct cf_def*,struct macro_params const*) ; 
 int /*<<< orphan*/  cf_preprocess_unwrap_param (struct cf_preprocessor*,struct darray*,struct cf_token**,struct cf_token const*,struct macro_param*) ; 
 int /*<<< orphan*/  darray_push_back (int,struct darray*,struct cf_token*) ; 
 struct macro_param* get_macro_param (struct macro_params const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cf_preprocess_addtoken(struct cf_preprocessor *pp,
				   struct darray *dst, /* struct cf_token */
				   struct cf_token **p_cur_token,
				   const struct cf_token *base,
				   const struct macro_params *params)
{
	struct cf_token *cur_token = *p_cur_token;

	if (pp->ignore_state)
		goto ignore;

	if (!base)
		base = cur_token;

	if (cur_token->type == CFTOKEN_NAME) {
		struct cf_def *def;
		struct macro_param *param;

		param = get_macro_param(params, &cur_token->str);
		if (param) {
			cf_preprocess_unwrap_param(pp, dst, &cur_token, base,
						   param);
			goto exit;
		}

		def = cf_preprocess_get_def(pp, &cur_token->str);
		if (def) {
			cf_preprocess_unwrap_define(pp, dst, &cur_token, base,
						    def, params);
			goto exit;
		}
	}

	darray_push_back(sizeof(struct cf_token), dst, cur_token);

ignore:
	cur_token++;

exit:
	*p_cur_token = cur_token;
}