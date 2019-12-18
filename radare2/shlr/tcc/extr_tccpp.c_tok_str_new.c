#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int last_line_num; scalar_t__ allocated_len; scalar_t__ len; int /*<<< orphan*/ * str; } ;
typedef  TYPE_1__ TokenString ;

/* Variables and functions */

void tok_str_new(TokenString *s)
{
	s->str = NULL;
	s->len = 0;
	s->allocated_len = 0;
	s->last_line_num = -1;
}