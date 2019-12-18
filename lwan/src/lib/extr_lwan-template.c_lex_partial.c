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
 int EOF ; 
 int /*<<< orphan*/  backup (struct lexer*) ; 
 int /*<<< orphan*/  ignore (struct lexer*) ; 
 scalar_t__ isident (int) ; 
 scalar_t__ isspace (int) ; 
 void* lex_error (struct lexer*,char*,...) ; 
 void* lex_identifier ; 
 int next (struct lexer*) ; 

__attribute__((used)) static void *lex_partial(struct lexer *lexer)
{
    while (true) {
        int r = next(lexer);

        if (r == EOF)
            return lex_error(lexer, "unexpected EOF while scanning action");
        if (r == '\n')
            return lex_error(lexer, "actions cannot span multiple lines");
        if (isspace(r)) {
            ignore(lexer);
            continue;
        }
        if (isident(r)) {
            backup(lexer);
            return lex_identifier;
        }
        return lex_error(lexer, "unexpected character: %c", r);
    }
}