#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* sym_label; } ;
struct TYPE_8__ {int r; struct TYPE_8__* prev_tok; } ;
typedef  TYPE_1__ Sym ;

/* Variables and functions */
 int TOK_IDENT ; 
 TYPE_1__* global_label_stack ; 
 TYPE_1__* sym_push2 (TYPE_1__**,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__** table_ident ; 

Sym *label_push(Sym **ptop, int v, int flags)
{
	Sym *s, **ps;
	s = sym_push2 (ptop, v, 0, 0);
	if (!s) {
		return s;
	}
	s->r = flags;
	ps = &table_ident[v - TOK_IDENT]->sym_label;
	if (ptop == &global_label_stack) {
		/* modify the top most local identifier, so that
		   sym_identifier will point to 's' when popped */
		while (*ps != NULL)
			ps = &(*ps)->prev_tok;
	}
	s->prev_tok = *ps;
	*ps = s;
	return s;
}