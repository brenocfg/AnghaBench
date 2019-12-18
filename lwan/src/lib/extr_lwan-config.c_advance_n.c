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
struct lexer {size_t pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  ignore (struct lexer*) ; 

__attribute__((used)) static void advance_n(struct lexer *lexer, size_t n)
{
    lexer->pos += n;
    ignore(lexer);
}