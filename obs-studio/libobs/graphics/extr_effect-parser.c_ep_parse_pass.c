#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ep_pass {int /*<<< orphan*/  name; } ;
struct TYPE_9__ {TYPE_2__* cur_token; } ;
struct effect_parser {TYPE_3__ cfp; } ;
struct cf_token {int /*<<< orphan*/  str; } ;
struct TYPE_7__ {int /*<<< orphan*/  len; int /*<<< orphan*/  array; } ;
struct TYPE_8__ {TYPE_1__ str; } ;

/* Variables and functions */
 int PARSE_CONTINUE ; 
 int PARSE_EOF ; 
 int PARSE_SUCCESS ; 
 int PARSE_UNEXPECTED_CONTINUE ; 
 int /*<<< orphan*/  bstrdup_n (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cf_next_token (TYPE_3__*) ; 
 int /*<<< orphan*/  cf_next_valid_token (TYPE_3__*) ; 
 int /*<<< orphan*/  cf_peek_valid_token (TYPE_3__*,struct cf_token*) ; 
 int /*<<< orphan*/  cf_token_is (TYPE_3__*,char*) ; 
 int ep_parse_pass_command (struct effect_parser*,struct ep_pass*) ; 
 scalar_t__ strref_cmp (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int ep_parse_pass(struct effect_parser *ep, struct ep_pass *pass)
{
	struct cf_token peek;

	if (!cf_token_is(&ep->cfp, "pass"))
		return PARSE_UNEXPECTED_CONTINUE;

	if (!cf_next_valid_token(&ep->cfp))
		return PARSE_EOF;

	if (!cf_token_is(&ep->cfp, "{")) {
		pass->name = bstrdup_n(ep->cfp.cur_token->str.array,
				       ep->cfp.cur_token->str.len);
		if (!cf_next_valid_token(&ep->cfp))
			return PARSE_EOF;
	}

	if (!cf_peek_valid_token(&ep->cfp, &peek))
		return PARSE_EOF;

	while (strref_cmp(&peek.str, "}") != 0) {
		int ret = ep_parse_pass_command(ep, pass);
		if (ret < 0 && ret != PARSE_CONTINUE)
			return ret;

		if (!cf_peek_valid_token(&ep->cfp, &peek))
			return PARSE_EOF;
	}

	/* token is '}' */
	cf_next_token(&ep->cfp);

	return PARSE_SUCCESS;
}