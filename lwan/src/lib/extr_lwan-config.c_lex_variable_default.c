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
 void* lex_config ; 
 void* lex_error (struct lexer*,char*) ; 
 int next (struct lexer*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void *lex_variable_default(struct lexer *lexer)
{
    int chr;

    do {
        chr = next(lexer);

        if (chr == '}') {
            backup(lexer);
            emit(lexer, LEXEME_STRING);

            advance_n(lexer, strlen("}"));

            return lex_config;
        }
    } while (chr != '\0');

    return lex_error(lexer, "EOF while scanning for end of variable");
}