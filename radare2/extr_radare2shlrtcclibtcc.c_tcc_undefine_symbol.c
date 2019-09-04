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
struct TYPE_3__ {int /*<<< orphan*/  tok; } ;
typedef  TYPE_1__ TokenSym ;
typedef  int /*<<< orphan*/  TCCState ;
typedef  int /*<<< orphan*/  Sym ;

/* Variables and functions */
 int /*<<< orphan*/ * define_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  define_undef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 TYPE_1__* tok_alloc (char const*,int /*<<< orphan*/ ) ; 

void tcc_undefine_symbol(TCCState *s1, const char *sym)
{
	TokenSym *ts;
	Sym *s;
	ts = tok_alloc (sym, strlen (sym));
	s = define_find (ts->tok);
	/* undefine symbol by putting an invalid name */
	if (s) {
		define_undef (s);
	}
}