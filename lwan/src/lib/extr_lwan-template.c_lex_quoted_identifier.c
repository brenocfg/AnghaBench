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
struct lexer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEXEME_CLOSE_CURLY_BRACE ; 
 int /*<<< orphan*/  LEXEME_OPEN_CURLY_BRACE ; 
 int /*<<< orphan*/  emit (struct lexer*,int /*<<< orphan*/ ) ; 
 void* lex_error (struct lexer*,char*,int) ; 
 int /*<<< orphan*/  lex_identifier (struct lexer*) ; 
 void* lex_inside_action ; 
 int next (struct lexer*) ; 

__attribute__((used)) static void *lex_quoted_identifier(struct lexer *lexer)
{
    int r;

    emit(lexer, LEXEME_OPEN_CURLY_BRACE);
    lex_identifier(lexer);

    r = next(lexer);
    if (r != '}')
        return lex_error(lexer, "expecting `}', found `%c'", r);

    emit(lexer, LEXEME_CLOSE_CURLY_BRACE);
    return lex_inside_action;
}