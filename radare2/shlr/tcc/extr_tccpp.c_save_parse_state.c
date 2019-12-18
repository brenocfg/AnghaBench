#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  line_num; } ;
struct TYPE_4__ {int /*<<< orphan*/  tokc; int /*<<< orphan*/  tok; int /*<<< orphan*/  macro_ptr; int /*<<< orphan*/  line_num; } ;
typedef  TYPE_1__ ParseState ;

/* Variables and functions */
 TYPE_3__* file ; 
 int /*<<< orphan*/  macro_ptr ; 
 int /*<<< orphan*/  tok ; 
 int /*<<< orphan*/  tokc ; 

void save_parse_state(ParseState *s)
{
	s->line_num = file->line_num;
	s->macro_ptr = macro_ptr;
	s->tok = tok;
	s->tokc = tokc;
}