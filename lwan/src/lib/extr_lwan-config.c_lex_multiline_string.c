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
struct lexer {int pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEXEME_STRING ; 
 int /*<<< orphan*/  advance_n (struct lexer*,scalar_t__) ; 
 int /*<<< orphan*/  emit (struct lexer*,int /*<<< orphan*/ ) ; 
 void* lex_config ; 
 void* lex_error (struct lexer*,char*) ; 
 scalar_t__ lex_streq (struct lexer*,char const*,int) ; 
 char next (struct lexer*) ; 
 char peek (struct lexer*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void *lex_multiline_string(struct lexer *lexer)
{
    const char *end = (peek(lexer) == '"') ? "\"\"\"" : "'''";

    advance_n(lexer, strlen("'''") - 1);

    do {
        if (lex_streq(lexer, end, 3)) {
            emit(lexer, LEXEME_STRING);
            lexer->pos += 3;

            return lex_config;
        }
    } while (next(lexer) != '\0');

    return lex_error(lexer, "EOF while scanning multiline string");
}