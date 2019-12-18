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
struct parser {int /*<<< orphan*/  stack; int /*<<< orphan*/  lexer; int /*<<< orphan*/  chunks; TYPE_1__* tpl; } ;
struct lwan_var_descriptor {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  chunks; } ;

/* Variables and functions */
 int /*<<< orphan*/  chunk_array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lex_init (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  list_head_init (int /*<<< orphan*/ *) ; 
 scalar_t__ symtab_push (struct parser*,struct lwan_var_descriptor const*) ; 

__attribute__((used)) static bool parser_init(struct parser *parser,
                        const struct lwan_var_descriptor *descriptor,
                        const char *string)
{
    if (symtab_push(parser, descriptor) < 0)
        return false;

    chunk_array_init(&parser->chunks);
    parser->tpl->chunks = parser->chunks;

    lex_init(&parser->lexer, string);
    list_head_init(&parser->stack);

    return true;
}