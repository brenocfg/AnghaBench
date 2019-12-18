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
struct TYPE_7__ {TYPE_1__* sym_define; } ;
struct TYPE_6__ {int* d; struct TYPE_6__* next; } ;
typedef  TYPE_1__ Sym ;

/* Variables and functions */
 int TOK_IDENT ; 
 TYPE_1__* define_find (int) ; 
 int /*<<< orphan*/  define_stack ; 
 int /*<<< orphan*/  get_tok_str (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  macro_is_equal (int*,int*) ; 
 TYPE_1__* sym_push2 (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 TYPE_2__** table_ident ; 
 int /*<<< orphan*/  tcc_warning (char*,int /*<<< orphan*/ ) ; 

void define_push(int v, int macro_type, int *str, Sym *first_arg)
{
	Sym *s;

	s = define_find (v);
	if (s && !macro_is_equal (s->d, str)) {
		tcc_warning ("%s redefined", get_tok_str (v, NULL));
	}

	s = sym_push2 (&define_stack, v, macro_type, 0);
	if (!s) {
		return;
	}
	s->d = str;
	s->next = first_arg;
	if (v >= TOK_IDENT) {
		table_ident[v - TOK_IDENT]->sym_define = s;
	}
}