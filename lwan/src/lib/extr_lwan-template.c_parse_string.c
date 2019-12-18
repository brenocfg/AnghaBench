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
struct parser {int template_flags; int /*<<< orphan*/  lexer; struct lwan_var_descriptor const* descriptor; int /*<<< orphan*/ * symtab; struct lwan_tpl* tpl; } ;
struct lwan_var_descriptor {int dummy; } ;
struct lwan_tpl {int dummy; } ;
typedef  struct lexeme lexeme ;
typedef  enum lwan_tpl_flag { ____Placeholder_lwan_tpl_flag } lwan_tpl_flag ;

/* Variables and functions */
 struct lexeme* lex_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parser_init (struct parser*,struct lwan_var_descriptor const*,char const*) ; 
 int parser_shutdown (struct parser*,struct lexeme*) ; 
 void* parser_text (struct parser*,struct lexeme*) ; 

__attribute__((used)) static bool parse_string(struct lwan_tpl *tpl,
                         const char *string,
                         const struct lwan_var_descriptor *descriptor,
                         enum lwan_tpl_flag flags)
{
    struct parser parser = {
        .tpl = tpl,
        .symtab = NULL,
        .descriptor = descriptor,
        .template_flags = flags
    };
    void *(*state)(struct parser *parser, struct lexeme *lexeme) = parser_text;
    struct lexeme *lexeme;

    if (!parser_init(&parser, descriptor, string))
        return false;

    while (state) {
        if (!(lexeme = lex_next(&parser.lexer)))
            break;

        state = state(&parser, lexeme);
    }

    return parser_shutdown(&parser, lexeme);
}