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
struct lexeme {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ LEXEME_ERROR ; 
 struct lexeme* lex_next_fsm_loop (struct lexer*) ; 

__attribute__((used)) static struct lexeme *lex_next(struct lexer *lexer)
{
    struct lexeme *lexeme = lex_next_fsm_loop(lexer);

    if (lexeme && lexeme->type == LEXEME_ERROR)
        return NULL;

    return lexeme;
}