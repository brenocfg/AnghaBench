#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct parser {int flags; } ;
struct lwan_var_descriptor {int /*<<< orphan*/  list_desc; } ;
struct TYPE_2__ {int /*<<< orphan*/  value; scalar_t__ len; } ;
struct lexeme {scalar_t__ type; TYPE_1__ value; } ;
typedef  enum flags { ____Placeholder_flags } flags ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_START_ITER ; 
 int ENODEV ; 
 int FLAGS_NEGATE ; 
 int FLAGS_NO_FREE ; 
 scalar_t__ LEXEME_IDENTIFIER ; 
 int /*<<< orphan*/  emit_chunk (struct parser*,int /*<<< orphan*/ ,int,struct lwan_var_descriptor*) ; 
 void* error_lexeme (struct lexeme*,char*,...) ; 
 int /*<<< orphan*/  parser_push_lexeme (struct parser*,struct lexeme*) ; 
 void* parser_right_meta ; 
 struct lwan_var_descriptor* symtab_lookup_lexeme (struct parser*,struct lexeme*) ; 
 int symtab_push (struct parser*,int /*<<< orphan*/ ) ; 
 void* unexpected_lexeme (struct lexeme*) ; 

__attribute__((used)) static void *parser_iter(struct parser *parser, struct lexeme *lexeme)
{
    if (lexeme->type == LEXEME_IDENTIFIER) {
        enum flags negate = parser->flags & FLAGS_NEGATE;
        struct lwan_var_descriptor *symbol =
            symtab_lookup_lexeme(parser, lexeme);
        if (!symbol) {
            return error_lexeme(lexeme, "Unknown variable: %.*s",
                                (int)lexeme->value.len, lexeme->value.value);
        }

        int r = symtab_push(parser, symbol->list_desc);
        if (r < 0) {
            if (r == -ENODEV) {
                return error_lexeme(
                    lexeme, "Couldn't find descriptor for variable `%.*s'",
                    (int)lexeme->value.len, lexeme->value.value);
            }
            return error_lexeme(lexeme,
                                "Could not push symbol table (out of memory)");
        }

        emit_chunk(parser, ACTION_START_ITER, negate | FLAGS_NO_FREE, symbol);

        parser_push_lexeme(parser, lexeme);
        parser->flags &= ~FLAGS_NEGATE;
        return parser_right_meta;
    }

    return unexpected_lexeme(lexeme);
}