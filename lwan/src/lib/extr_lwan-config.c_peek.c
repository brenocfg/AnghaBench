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
 int next (struct lexer*) ; 

__attribute__((used)) static int peek(struct lexer *lexer)
{
    int chr = next(lexer);

    backup(lexer);

    return chr;
}