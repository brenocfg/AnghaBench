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
struct TYPE_3__ {char* array; } ;
struct cf_token {scalar_t__ type; TYPE_1__ str; } ;
struct cf_preprocessor {int /*<<< orphan*/  defines; scalar_t__ ignore_state; } ;
struct TYPE_4__ {int /*<<< orphan*/  da; } ;
struct cf_def {TYPE_2__ tokens; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ CFTOKEN_NAME ; 
 scalar_t__ CFTOKEN_NEWLINE ; 
 scalar_t__ CFTOKEN_NONE ; 
 int /*<<< orphan*/  append_end_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  append_space (struct cf_preprocessor*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cf_adderror_expecting (struct cf_preprocessor*,struct cf_token*,char*) ; 
 int /*<<< orphan*/  cf_def_addtoken (struct cf_def*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cf_def_free (struct cf_def*) ; 
 int /*<<< orphan*/  cf_def_init (struct cf_def*) ; 
 int /*<<< orphan*/  cf_preprocess_macro_params (struct cf_preprocessor*,struct cf_def*,struct cf_token**) ; 
 int /*<<< orphan*/  cf_token_copy (int /*<<< orphan*/ *,struct cf_token*) ; 
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,struct cf_def*) ; 
 int /*<<< orphan*/  go_to_newline (struct cf_token**) ; 
 int /*<<< orphan*/  next_token (struct cf_token**,int) ; 

__attribute__((used)) static void cf_preprocess_define(struct cf_preprocessor *pp,
				 struct cf_token **p_cur_token)
{
	struct cf_token *cur_token = *p_cur_token;
	struct cf_def def;

	if (pp->ignore_state) {
		go_to_newline(p_cur_token);
		return;
	}

	cf_def_init(&def);

	next_token(&cur_token, true);
	if (cur_token->type != CFTOKEN_NAME) {
		cf_adderror_expecting(pp, cur_token, "identifier");
		go_to_newline(&cur_token);
		goto exit;
	}

	append_space(pp, &def.tokens.da, NULL);
	cf_token_copy(&def.name, cur_token);

	if (!next_token(&cur_token, true))
		goto complete;

	/* process macro */
	if (*cur_token->str.array == '(') {
		if (!cf_preprocess_macro_params(pp, &def, &cur_token))
			goto error;
	}

	while (cur_token->type != CFTOKEN_NEWLINE &&
	       cur_token->type != CFTOKEN_NONE)
		cf_def_addtoken(&def, cur_token++);

complete:
	append_end_token(&def.tokens.da);
	append_space(pp, &def.tokens.da, NULL);
	da_push_back(pp->defines, &def);
	goto exit;

error:
	cf_def_free(&def);

exit:
	*p_cur_token = cur_token;
}