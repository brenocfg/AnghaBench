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
struct lexer {int* pos; int* end; int /*<<< orphan*/  cur_line; } ;

/* Variables and functions */

__attribute__((used)) static int next(struct lexer *lexer)
{
    if (lexer->pos >= lexer->end) {
        lexer->pos = lexer->end + 1;
        return '\0';
    }

    int r = *lexer->pos;
    lexer->pos++;

    if (r == '\n')
        lexer->cur_line++;

    return r;
}