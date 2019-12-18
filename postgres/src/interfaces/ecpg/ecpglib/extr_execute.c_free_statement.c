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
struct statement {struct statement* oldlocale; scalar_t__ clocale; struct statement* name; struct statement* command; int /*<<< orphan*/  outlist; int /*<<< orphan*/  inlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  ecpg_free (struct statement*) ; 
 int /*<<< orphan*/  free_variable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freelocale (scalar_t__) ; 

__attribute__((used)) static void
free_statement(struct statement *stmt)
{
	if (stmt == NULL)
		return;
	free_variable(stmt->inlist);
	free_variable(stmt->outlist);
	ecpg_free(stmt->command);
	ecpg_free(stmt->name);
#ifdef HAVE_USELOCALE
	if (stmt->clocale)
		freelocale(stmt->clocale);
#else
	ecpg_free(stmt->oldlocale);
#endif
	ecpg_free(stmt);
}