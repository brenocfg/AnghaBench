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
struct dstr {int /*<<< orphan*/  array; } ;
struct cf_token {scalar_t__ type; int /*<<< orphan*/  str; } ;
struct cf_preprocessor {int dummy; } ;

/* Variables and functions */
 scalar_t__ CFTOKEN_NEWLINE ; 
 scalar_t__ CFTOKEN_NONE ; 
 int /*<<< orphan*/  cf_adderror (struct cf_preprocessor*,struct cf_token*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cf_preprocess_define (struct cf_preprocessor*,struct cf_token**) ; 
 int /*<<< orphan*/  cf_preprocess_ifdef (struct cf_preprocessor*,int,struct cf_token**) ; 
 int /*<<< orphan*/  cf_preprocess_include (struct cf_preprocessor*,struct cf_token**) ; 
 int /*<<< orphan*/  cf_preprocess_undef (struct cf_preprocessor*,struct cf_token**) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_init_copy_strref (struct dstr*,int /*<<< orphan*/ *) ; 
 scalar_t__ strref_cmp (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static bool cf_preprocessor(struct cf_preprocessor *pp, bool if_block,
			    struct cf_token **p_cur_token)
{
	struct cf_token *cur_token = *p_cur_token;

	if (strref_cmp(&cur_token->str, "include") == 0) {
		cf_preprocess_include(pp, p_cur_token);

	} else if (strref_cmp(&cur_token->str, "define") == 0) {
		cf_preprocess_define(pp, p_cur_token);

	} else if (strref_cmp(&cur_token->str, "undef") == 0) {
		cf_preprocess_undef(pp, p_cur_token);

	} else if (strref_cmp(&cur_token->str, "ifdef") == 0) {
		cf_preprocess_ifdef(pp, false, p_cur_token);

	} else if (strref_cmp(&cur_token->str, "ifndef") == 0) {
		cf_preprocess_ifdef(pp, true, p_cur_token);

		/*} else if (strref_cmp(&cur_token->str, "if") == 0) {
		TODO;*/
	} else if (strref_cmp(&cur_token->str, "else") == 0 ||
		   /*strref_cmp(&cur_token->str, "elif") == 0 ||*/
		   strref_cmp(&cur_token->str, "endif") == 0) {
		if (!if_block) {
			struct dstr name;
			dstr_init_copy_strref(&name, &cur_token->str);
			cf_adderror(pp, cur_token,
				    "#$1 outside of "
				    "#if/#ifdef/#ifndef block",
				    name.array, NULL, NULL);
			dstr_free(&name);
			(*p_cur_token)++;

			return true;
		}

		return false;

	} else if (cur_token->type != CFTOKEN_NEWLINE &&
		   cur_token->type != CFTOKEN_NONE) {
		/*
		 * TODO: language-specific preprocessor stuff should be sent to
		 * handler of some sort
		 */
		(*p_cur_token)++;
	}

	return true;
}