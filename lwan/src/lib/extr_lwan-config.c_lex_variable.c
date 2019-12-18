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
 int /*<<< orphan*/  LEXEME_VARIABLE ; 
 int /*<<< orphan*/  LEXEME_VARIABLE_DEFAULT ; 
 int /*<<< orphan*/  advance_n (struct lexer*,scalar_t__) ; 
 int /*<<< orphan*/  backup (struct lexer*) ; 
 int /*<<< orphan*/  emit (struct lexer*,int /*<<< orphan*/ ) ; 
 scalar_t__ isvariable (int) ; 
 void* lex_config ; 
 void* lex_error (struct lexer*,char*) ; 
 void* lex_variable_default ; 
 int next (struct lexer*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void *lex_variable(struct lexer *lexer)
{
    int chr;

    advance_n(lexer, strlen("${") - 1);

    do {
        chr = next(lexer);

        if (chr == ':') {
            backup(lexer);
            emit(lexer, LEXEME_VARIABLE_DEFAULT);
            advance_n(lexer, strlen(":"));
            return lex_variable_default;
        }

        if (chr == '}') {
            backup(lexer);
            emit(lexer, LEXEME_VARIABLE);
            advance_n(lexer, strlen("}"));

            return lex_config;
        }
    } while (isvariable(chr));

    return lex_error(lexer, "EOF while scanning for end of variable");
}