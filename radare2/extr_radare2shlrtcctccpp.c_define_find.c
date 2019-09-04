#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * sym_define; } ;
typedef  int /*<<< orphan*/  Sym ;

/* Variables and functions */
 scalar_t__ TOK_IDENT ; 
 TYPE_1__** table_ident ; 
 scalar_t__ tok_ident ; 

Sym *define_find(int v)
{
	v -= TOK_IDENT;
	if ((unsigned) v >= (unsigned) (tok_ident - TOK_IDENT)) {
		return NULL;
	}
	return table_ident[v]->sym_define;
}