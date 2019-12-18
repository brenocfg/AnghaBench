#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ last_line_num; } ;
typedef  TYPE_1__ TokenString ;
struct TYPE_10__ {scalar_t__ line_num; } ;
struct TYPE_9__ {scalar_t__ i; } ;
typedef  TYPE_2__ CValue ;

/* Variables and functions */
 int /*<<< orphan*/  TOK_LINENUM ; 
 TYPE_7__* file ; 
 int /*<<< orphan*/  tok ; 
 int /*<<< orphan*/  tok_str_add2 (TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__ tokc ; 

void tok_str_add_tok(TokenString *s)
{
	CValue cval;

	/* save line number info */
	if (file->line_num != s->last_line_num) {
		s->last_line_num = file->line_num;
		cval.i = s->last_line_num;
		tok_str_add2 (s, TOK_LINENUM, &cval);
	}
	tok_str_add2 (s, tok, &tokc);
}