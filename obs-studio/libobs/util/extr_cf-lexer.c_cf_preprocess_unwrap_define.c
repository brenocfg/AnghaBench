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
struct macro_params {int dummy; } ;
struct darray {int dummy; } ;
struct cf_token {scalar_t__ type; } ;
struct cf_preprocessor {int dummy; } ;
struct TYPE_2__ {struct cf_token* array; } ;
struct cf_def {scalar_t__ macro; TYPE_1__ tokens; } ;

/* Variables and functions */
 scalar_t__ CFTOKEN_NONE ; 
 int /*<<< orphan*/  cf_preprocess_addtoken (struct cf_preprocessor*,struct darray*,struct cf_token**,struct cf_token const*,struct macro_params*) ; 
 int /*<<< orphan*/  cf_preprocess_save_macro_params (struct cf_preprocessor*,struct cf_token**,struct cf_def const*,struct cf_token const*,struct macro_params const*,struct macro_params*) ; 
 int /*<<< orphan*/  macro_params_free (struct macro_params*) ; 
 int /*<<< orphan*/  macro_params_init (struct macro_params*) ; 

__attribute__((used)) static inline void cf_preprocess_unwrap_define(
	struct cf_preprocessor *pp, struct darray *dst, /* struct cf_token */
	struct cf_token **p_cur_token, const struct cf_token *base,
	const struct cf_def *def, const struct macro_params *cur_params)
{
	struct cf_token *cur_token = *p_cur_token;
	struct macro_params new_params;
	struct cf_token *cur_def_token = def->tokens.array;

	macro_params_init(&new_params);

	if (def->macro)
		cf_preprocess_save_macro_params(pp, &cur_token, def, base,
						cur_params, &new_params);

	while (cur_def_token->type != CFTOKEN_NONE)
		cf_preprocess_addtoken(pp, dst, &cur_def_token, base,
				       &new_params);

	macro_params_free(&new_params);

	cur_token++;
	*p_cur_token = cur_token;
}