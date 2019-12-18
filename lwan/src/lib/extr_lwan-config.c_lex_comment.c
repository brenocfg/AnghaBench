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
 int /*<<< orphan*/  backup (struct lexer*) ; 
 scalar_t__ iscomment (int /*<<< orphan*/ ) ; 
 void* lex_config ; 
 int /*<<< orphan*/  next (struct lexer*) ; 

__attribute__((used)) static void *lex_comment(struct lexer *lexer)
{
    while (iscomment(next(lexer)))
        ;
    backup(lexer);
    return lex_config;
}