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
struct lexer {scalar_t__ pos; scalar_t__ start; } ;

/* Variables and functions */
 scalar_t__ EOF ; 
 int /*<<< orphan*/  LEXEME_EOF ; 
 int /*<<< orphan*/  LEXEME_TEXT ; 
 int /*<<< orphan*/  emit (struct lexer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  left_meta ; 
 void* lex_error (struct lexer*,char*) ; 
 void* lex_left_meta ; 
 scalar_t__ lex_streq (struct lexer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ next (struct lexer*) ; 
 int /*<<< orphan*/  right_meta ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *lex_text(struct lexer *lexer)
{
    do {
        if (lex_streq(lexer, left_meta, strlen(left_meta))) {
            if (lexer->pos > lexer->start)
                emit(lexer, LEXEME_TEXT);
            return lex_left_meta;
        }

        if (lex_streq(lexer, right_meta, strlen(right_meta)))
            return lex_error(lexer, "unexpected action close sequence");
    } while (next(lexer) != EOF);
    if (lexer->pos > lexer->start)
        emit(lexer, LEXEME_TEXT);
    emit(lexer, LEXEME_EOF);
    return NULL;
}