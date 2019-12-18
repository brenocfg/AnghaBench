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
struct lexer {int /*<<< orphan*/  pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEXEME_LEFT_META ; 
 int /*<<< orphan*/  backup (struct lexer*) ; 
 int /*<<< orphan*/  emit (struct lexer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  left_meta ; 
 void* lex_comment ; 
 void* lex_inside_action ; 
 int next (struct lexer*) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *lex_left_meta(struct lexer *lexer)
{
    lexer->pos += strlen(left_meta);
    int r = next(lexer);
    if (r == '!')
        return lex_comment;
    backup(lexer);

    emit(lexer, LEXEME_LEFT_META);
    return lex_inside_action;
}