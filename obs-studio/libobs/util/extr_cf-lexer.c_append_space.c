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
struct darray {int dummy; } ;
struct cf_token {int /*<<< orphan*/  str; int /*<<< orphan*/  unmerged_str; int /*<<< orphan*/  lex; int /*<<< orphan*/  type; } ;
struct cf_preprocessor {int /*<<< orphan*/  lex; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFTOKEN_SPACETAB ; 
 int /*<<< orphan*/  darray_push_back (int,struct darray*,struct cf_token*) ; 
 int /*<<< orphan*/  space_filler ; 
 int /*<<< orphan*/  strref_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strref_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void append_space(struct cf_preprocessor *pp,
				struct darray *tokens,
				const struct cf_token *base)
{
	struct cf_token token;

	strref_set(&token.str, space_filler, 1);
	token.type = CFTOKEN_SPACETAB;
	if (base) {
		token.lex = base->lex;
		strref_copy(&token.unmerged_str, &base->unmerged_str);
	} else {
		token.lex = pp->lex;
		strref_copy(&token.unmerged_str, &token.str);
	}

	darray_push_back(sizeof(struct cf_token), tokens, &token);
}