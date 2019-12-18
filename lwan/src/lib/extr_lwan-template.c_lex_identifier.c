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
 int /*<<< orphan*/  LEXEME_IDENTIFIER ; 
 int /*<<< orphan*/  backup (struct lexer*) ; 
 int /*<<< orphan*/  emit (struct lexer*,int /*<<< orphan*/ ) ; 
 scalar_t__ isident (int /*<<< orphan*/ ) ; 
 void* lex_inside_action ; 
 int /*<<< orphan*/  next (struct lexer*) ; 

__attribute__((used)) static void *lex_identifier(struct lexer *lexer)
{
    while (isident(next(lexer)))
        ;
    backup(lexer);
    emit(lexer, LEXEME_IDENTIFIER);
    return lex_inside_action;
}