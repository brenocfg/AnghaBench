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
struct decl_info {int dummy; } ;
struct cf_token {scalar_t__ type; } ;
struct cf_parser {int dummy; } ;

/* Variables and functions */
 scalar_t__ CFTOKEN_NAME ; 
 int PARSE_CONTINUE ; 
 int PARSE_EOF ; 
 int /*<<< orphan*/  cf_next_token_should_be (struct cf_parser*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cf_next_valid_token (struct cf_parser*) ; 
 int /*<<< orphan*/  cf_peek_valid_token (struct cf_parser*,struct cf_token*) ; 
 scalar_t__ cf_token_is (struct cf_parser*,char*) ; 
 int cf_token_should_be (struct cf_parser*,char*,char*,int /*<<< orphan*/ *) ; 
 int parse_param (struct cf_parser*,struct decl_info*) ; 

__attribute__((used)) static void parse_params(struct cf_parser *cfp, struct decl_info *decl)
{
	struct cf_token peek;
	int code;

	if (!cf_peek_valid_token(cfp, &peek))
		return;

	while (peek.type == CFTOKEN_NAME) {
		code = parse_param(cfp, decl);
		if (code == PARSE_EOF)
			return;

		if (code != PARSE_CONTINUE && !cf_next_valid_token(cfp))
			return;

		if (cf_token_is(cfp, ")"))
			break;
		else if (cf_token_should_be(cfp, ",", ",", NULL) == PARSE_EOF)
			return;

		if (!cf_peek_valid_token(cfp, &peek))
			return;
	}

	if (!cf_token_is(cfp, ")"))
		cf_next_token_should_be(cfp, ")", NULL, NULL);
}