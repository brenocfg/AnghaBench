#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * sym_define; } ;
struct TYPE_6__ {int v; scalar_t__ d; struct TYPE_6__* prev; } ;
typedef  TYPE_1__ Sym ;

/* Variables and functions */
 int TOK_IDENT ; 
 TYPE_1__* define_stack ; 
 int /*<<< orphan*/  sym_free (TYPE_1__*) ; 
 TYPE_2__** table_ident ; 
 int tok_ident ; 
 int /*<<< orphan*/  tok_str_free (scalar_t__) ; 

void free_defines(Sym *b)
{
	Sym *top, *top1;
	int v;

	top = define_stack;
	while (top != b) {
		top1 = top->prev;
		/* do not free args or predefined defines */
		if (top->d) {
			tok_str_free (top->d);
		}
		v = top->v;
		if (v >= TOK_IDENT && v < tok_ident) {
			table_ident[v - TOK_IDENT]->sym_define = NULL;
		}
		sym_free (top);
		top = top1;
	}
	define_stack = b;
}