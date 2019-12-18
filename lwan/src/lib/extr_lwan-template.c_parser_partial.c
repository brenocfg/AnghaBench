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
struct parser {int /*<<< orphan*/  descriptor; } ;
struct lwan_tpl {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  value; } ;
struct lexeme {scalar_t__ type; TYPE_1__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_APPLY_TPL ; 
 scalar_t__ LEXEME_IDENTIFIER ; 
 int /*<<< orphan*/  emit_chunk (struct parser*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct lwan_tpl*) ; 
 void* error_lexeme (struct lexeme*,char*,char*) ; 
 struct lwan_tpl* lwan_tpl_compile_file (char*,int /*<<< orphan*/ ) ; 
 void* parser_right_meta ; 
 char* strndupa (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* unexpected_lexeme (struct lexeme*) ; 

__attribute__((used)) static void *parser_partial(struct parser *parser, struct lexeme *lexeme)
{
    struct lwan_tpl *tpl;
    char *filename = strndupa(lexeme->value.value, lexeme->value.len);

    if (lexeme->type != LEXEME_IDENTIFIER)
        return unexpected_lexeme(lexeme);

    tpl = lwan_tpl_compile_file(filename, parser->descriptor);
    if (tpl) {
        emit_chunk(parser, ACTION_APPLY_TPL, 0, tpl);
        return parser_right_meta;
    }

    return error_lexeme(lexeme, "Could not compile template ``%s''", filename);
}