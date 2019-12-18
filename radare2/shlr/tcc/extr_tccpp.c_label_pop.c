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
struct TYPE_7__ {int /*<<< orphan*/  sym_label; } ;
struct TYPE_6__ {scalar_t__ r; size_t v; int /*<<< orphan*/  prev_tok; struct TYPE_6__* prev; } ;
typedef  TYPE_1__ Sym ;

/* Variables and functions */
 scalar_t__ LABEL_DECLARED ; 
 scalar_t__ LABEL_FORWARD ; 
 size_t TOK_IDENT ; 
 int /*<<< orphan*/  get_tok_str (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sym_free (TYPE_1__*) ; 
 TYPE_2__** table_ident ; 
 int /*<<< orphan*/  tcc_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcc_warning (char*,int /*<<< orphan*/ ) ; 

void label_pop(Sym **ptop, Sym *slast)
{
	Sym *s, *s1;
	for (s = *ptop; s != slast; s = s1) {
		s1 = s->prev;
		if (s->r == LABEL_DECLARED) {
			tcc_warning ("label '%s' declared but not used", get_tok_str (s->v, NULL));
		} else if (s->r == LABEL_FORWARD) {
			tcc_error ("label '%s' used but not defined",
				get_tok_str (s->v, NULL));
		}
		/* remove label */
		table_ident[s->v - TOK_IDENT]->sym_label = s->prev_tok;
		sym_free (s);
	}
	*ptop = slast;
}