#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* sym_identifier; } ;
struct TYPE_5__ {struct TYPE_5__* prev_tok; } ;
typedef  TYPE_1__ Sym ;

/* Variables and functions */
 int SYM_FIRST_ANOM ; 
 int SYM_STRUCT ; 
 int TOK_IDENT ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  global_stack ; 
 TYPE_1__* sym_push2 (int /*<<< orphan*/ *,int,int,long long) ; 
 TYPE_2__** table_ident ; 

Sym *global_identifier_push(int v, int t, long long c) {
	Sym *s, **ps;
	s = sym_push2 (&global_stack, v, t, c);
	/* don't record anonymous symbol */
	if (s && v < SYM_FIRST_ANOM) {
		int i = (v & ~SYM_STRUCT);
		if (i < TOK_IDENT) {
			eprintf ("Not found\n");
			return NULL;
		}
		ps = &table_ident[i - TOK_IDENT]->sym_identifier;
		/* modify the top most local identifier, so that
		   sym_identifier will point to 's' when popped */
		while (*ps) {
			ps = &(*ps)->prev_tok;
		}
		s->prev_tok = NULL;
		*ps = s;
	}
	return s;
}