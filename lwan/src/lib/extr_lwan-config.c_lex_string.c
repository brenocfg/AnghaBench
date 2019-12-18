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
 int /*<<< orphan*/  LEXEME_STRING ; 
 int /*<<< orphan*/  advance_n (struct lexer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  backup (struct lexer*) ; 
 int /*<<< orphan*/  emit (struct lexer*,int /*<<< orphan*/ ) ; 
 scalar_t__ isstring (int) ; 
 void* lex_config ; 
 void* lex_variable ; 
 int next (struct lexer*) ; 
 char peek (struct lexer*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void *lex_string(struct lexer *lexer)
{
    int chr;

    do {
        chr = next(lexer);

        if (chr == '$' && peek(lexer) == '{') {
            backup(lexer);
            emit(lexer, LEXEME_STRING);

            advance_n(lexer, strlen("{"));

            return lex_variable;
        }
    } while (isstring(chr));

    backup(lexer);
    emit(lexer, LEXEME_STRING);

    return lex_config;
}