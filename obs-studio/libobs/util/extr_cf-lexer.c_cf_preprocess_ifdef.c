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
struct cf_preprocessor {int dummy; } ;
struct cf_def {int dummy; } ;

/* Variables and functions */
 scalar_t__ CFTOKEN_NAME ; 
 int /*<<< orphan*/  cf_adderror_expecting (struct cf_preprocessor*,struct cf_token*,char*) ; 
 struct cf_def* cf_preprocess_get_def (struct cf_preprocessor*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cf_preprocess_subblock (struct cf_preprocessor*,int,struct cf_token**) ; 
 int /*<<< orphan*/  go_to_newline (struct cf_token**) ; 
 int /*<<< orphan*/  next_token (struct cf_token**,int) ; 
 scalar_t__ strref_cmp (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void cf_preprocess_ifdef(struct cf_preprocessor *pp, bool ifnot,
				struct cf_token **p_cur_token)
{
	struct cf_token *cur_token = *p_cur_token;
	struct cf_def *def;
	bool is_true;

	next_token(&cur_token, true);
	if (cur_token->type != CFTOKEN_NAME) {
		cf_adderror_expecting(pp, cur_token, "identifier");
		go_to_newline(&cur_token);
		goto exit;
	}

	def = cf_preprocess_get_def(pp, &cur_token->str);
	is_true = (def == NULL) == ifnot;

	if (!cf_preprocess_subblock(pp, !is_true, &cur_token))
		goto exit;

	if (strref_cmp(&cur_token->str, "else") == 0) {
		if (!cf_preprocess_subblock(pp, is_true, &cur_token))
			goto exit;
		/*} else if (strref_cmp(&cur_token->str, "elif") == 0) {*/
	}

	cur_token++;

exit:
	*p_cur_token = cur_token;
}