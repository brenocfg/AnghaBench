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
struct parser {int stack_pos; int* stack; } ;
typedef  enum parser_state { ____Placeholder_parser_state } parser_state ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 

__attribute__((used)) static inline void push_state( struct parser *parser, enum parser_state state )
{
    ASSERT( parser->stack_pos < sizeof(parser->stack)/sizeof(parser->stack[0]) );
    parser->stack[parser->stack_pos++] = state;
}