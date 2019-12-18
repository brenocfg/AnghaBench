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
 int /*<<< orphan*/  ignore (struct lexer*) ; 
 int /*<<< orphan*/  left_meta ; 
 void* lex_error (struct lexer*,char*) ; 
 void* lex_text ; 
 int next (struct lexer*) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *lex_comment(struct lexer *lexer)
{
    size_t brackets = strlen(left_meta);

    do {
        int r = next(lexer);
        if (r == '{')
            brackets++;
        else if (r == '}')
            brackets--;
        else if (r == EOF)
            return lex_error(lexer,
                             "unexpected EOF while scanning comment end");
    } while (brackets);

    ignore(lexer);
    return lex_text;
}