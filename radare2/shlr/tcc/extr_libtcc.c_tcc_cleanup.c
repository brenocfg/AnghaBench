#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int TOK_IDENT ; 
 int /*<<< orphan*/  cstr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dynarray_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *****) ; 
 int /*<<< orphan*/  free_defines (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * macro_ptr ; 
 int /*<<< orphan*/  nb_sym_pools ; 
 int /*<<< orphan*/ * sym_free_first ; 
 int /*<<< orphan*/  sym_pools ; 
 int /*<<< orphan*/ ***** table_ident ; 
 int /*<<< orphan*/ * tcc_state ; 
 int tok_ident ; 
 int /*<<< orphan*/  tokcstr ; 

__attribute__((used)) static void tcc_cleanup(void)
{
	int i, n;
	if (NULL == tcc_state) {
		return;
	}
	tcc_state = NULL;

	/* free -D defines */
	free_defines (NULL);

	/* free tokens */
	n = tok_ident - TOK_IDENT;
	for (i = 0; i < n; i++) {
		free (table_ident[i]);
	}
	free (table_ident);

	/* free sym_pools */
	dynarray_reset (&sym_pools, &nb_sym_pools);
	/* string buffer */
	cstr_free (&tokcstr);
	/* reset symbol stack */
	sym_free_first = NULL;
	/* cleanup from error/setjmp */
	macro_ptr = NULL;
}