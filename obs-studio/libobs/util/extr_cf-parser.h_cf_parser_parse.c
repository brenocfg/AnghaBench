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
struct cf_parser {int /*<<< orphan*/  pp; int /*<<< orphan*/  cur_token; int /*<<< orphan*/  error_list; int /*<<< orphan*/  lex; } ;

/* Variables and functions */
 int /*<<< orphan*/  cf_lexer_lex (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  cf_preprocess (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cf_preprocessor_get_tokens (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool cf_parser_parse(struct cf_parser *parser, const char *str,
				   const char *file)
{
	if (!cf_lexer_lex(&parser->lex, str, file))
		return false;

	if (!cf_preprocess(&parser->pp, &parser->lex, &parser->error_list))
		return false;

	parser->cur_token = cf_preprocessor_get_tokens(&parser->pp);
	return true;
}