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
 size_t remaining (struct lexer*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char const*,size_t) ; 

__attribute__((used)) static bool lex_streq(struct lexer *lexer, const char *str, size_t s)
{
    if (remaining(lexer) < s)
        return false;

    return !strncmp(lexer->pos, str, s);
}