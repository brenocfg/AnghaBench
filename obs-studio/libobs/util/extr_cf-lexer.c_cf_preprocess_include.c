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
 scalar_t__ CFTOKEN_STRING ; 
 int /*<<< orphan*/  cf_adderror (struct cf_preprocessor*,struct cf_token*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cf_adderror_expecting (struct cf_preprocessor*,struct cf_token*,char*) ; 
 int /*<<< orphan*/  cf_include_file (struct cf_preprocessor*,struct cf_token*) ; 
 int /*<<< orphan*/  go_to_newline (struct cf_token**) ; 
 scalar_t__ is_loc_include (int /*<<< orphan*/ *) ; 
 scalar_t__ is_sys_include (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next_token (struct cf_token**,int) ; 

__attribute__((used)) static void cf_preprocess_include(struct cf_preprocessor *pp,
				  struct cf_token **p_cur_token)
{
	struct cf_token *cur_token = *p_cur_token;

	if (pp->ignore_state) {
		go_to_newline(p_cur_token);
		return;
	}

	next_token(&cur_token, true);

	if (cur_token->type != CFTOKEN_STRING) {
		cf_adderror_expecting(pp, cur_token, "string");
		go_to_newline(&cur_token);
		goto exit;
	}

	if (is_sys_include(&cur_token->str)) {
		/* TODO */
	} else if (is_loc_include(&cur_token->str)) {
		if (!pp->ignore_state)
			cf_include_file(pp, cur_token);
	} else {
		cf_adderror(pp, cur_token, "Invalid or incomplete string", NULL,
			    NULL, NULL);
		go_to_newline(&cur_token);
		goto exit;
	}

	cur_token++;

exit:
	*p_cur_token = cur_token;
}