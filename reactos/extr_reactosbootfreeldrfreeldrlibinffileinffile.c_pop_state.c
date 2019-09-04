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
struct parser {size_t stack_pos; int /*<<< orphan*/ * stack; int /*<<< orphan*/  state; } ;

/* Variables and functions */

__attribute__((used)) __inline static void pop_state(struct parser *parser)
{
//  assert( parser->stack_pos );
    parser->state = parser->stack[--parser->stack_pos];
}