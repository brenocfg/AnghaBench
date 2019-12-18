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
struct cf_token {scalar_t__ type; int /*<<< orphan*/  str; } ;
struct cf_preprocessor {scalar_t__ ignore_state; } ;

/* Variables and functions */
 scalar_t__ CFTOKEN_NAME ; 
 int /*<<< orphan*/  cf_adderror_expecting (struct cf_preprocessor*,struct cf_token*,char*) ; 
 int /*<<< orphan*/  cf_preprocess_remove_def_strref (struct cf_preprocessor*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  go_to_newline (struct cf_token**) ; 
 int /*<<< orphan*/  next_token (struct cf_token**,int) ; 

__attribute__((used)) static void cf_preprocess_undef(struct cf_preprocessor *pp,
				struct cf_token **p_cur_token)
{
	struct cf_token *cur_token = *p_cur_token;

	if (pp->ignore_state) {
		go_to_newline(p_cur_token);
		return;
	}

	next_token(&cur_token, true);
	if (cur_token->type != CFTOKEN_NAME) {
		cf_adderror_expecting(pp, cur_token, "identifier");
		go_to_newline(&cur_token);
		goto exit;
	}

	cf_preprocess_remove_def_strref(pp, &cur_token->str);
	cur_token++;

exit:
	*p_cur_token = cur_token;
}