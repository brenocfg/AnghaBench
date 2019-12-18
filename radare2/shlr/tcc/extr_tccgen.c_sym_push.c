#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_3__* sym_identifier; TYPE_3__* sym_struct; } ;
typedef  TYPE_2__ TokenSym ;
struct TYPE_15__ {int /*<<< orphan*/  ref; int /*<<< orphan*/  t; } ;
struct TYPE_12__ {int /*<<< orphan*/  ref; } ;
struct TYPE_14__ {int r; struct TYPE_14__* prev_tok; TYPE_1__ type; } ;
typedef  TYPE_3__ Sym ;
typedef  TYPE_4__ CType ;

/* Variables and functions */
 int SYM_FIELD ; 
 int SYM_FIRST_ANOM ; 
 int SYM_STRUCT ; 
 int TOK_IDENT ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 TYPE_3__* global_stack ; 
 TYPE_3__* local_stack ; 
 TYPE_3__* sym_push2 (TYPE_3__**,int,int /*<<< orphan*/ ,long long) ; 
 TYPE_2__** table_ident ; 

Sym *sym_push(int v, CType *type, int r, long long c) {
	Sym *s, **ps;
	TokenSym *ts;

	if (local_stack) {
		ps = &local_stack;
	} else {
		ps = &global_stack;
	}
	// dump_type(type, 5);
	s = sym_push2 (ps, v, type->t, c);
	if (!s) {
		return NULL;
	}
	s->type.ref = type->ref;
	s->r = r;
	/* don't record fields or anonymous symbols */
	/* XXX: simplify */
	if (!(v & SYM_FIELD) && (v & ~SYM_STRUCT) < SYM_FIRST_ANOM) {
		int i = (v & ~SYM_STRUCT);
		if (i < TOK_IDENT) {
			eprintf ("Not found\n");
			return NULL;
		}
		// ts = table_ident[i - TOK_IDENT];
		/* record symbol in token array */
		ts = table_ident[(v & ~SYM_STRUCT) - TOK_IDENT];
		if (v & SYM_STRUCT) {
			ps = &ts->sym_struct;
		} else {
			ps = &ts->sym_identifier;
		}
		s->prev_tok = *ps;
		*ps = s;
	}
	return s;
}