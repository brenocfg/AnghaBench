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
struct TYPE_2__ {struct cf_token* array; } ;
struct macro_param {TYPE_1__ tokens; } ;
struct darray {int dummy; } ;
struct cf_token {scalar_t__ type; } ;
struct cf_preprocessor {int dummy; } ;

/* Variables and functions */
 scalar_t__ CFTOKEN_NONE ; 
 int /*<<< orphan*/  cf_preprocess_addtoken (struct cf_preprocessor*,struct darray*,struct cf_token**,struct cf_token const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void cf_preprocess_unwrap_param(
	struct cf_preprocessor *pp, struct darray *dst, /* struct cf_token */
	struct cf_token **p_cur_token, const struct cf_token *base,
	const struct macro_param *param)
{
	struct cf_token *cur_token = *p_cur_token;
	struct cf_token *cur_param_token = param->tokens.array;

	while (cur_param_token->type != CFTOKEN_NONE)
		cf_preprocess_addtoken(pp, dst, &cur_param_token, base, NULL);

	cur_token++;
	*p_cur_token = cur_token;
}