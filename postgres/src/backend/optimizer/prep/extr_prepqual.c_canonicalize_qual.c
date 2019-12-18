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
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  IsA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  List ; 
 int /*<<< orphan*/ * find_duplicate_ors (int /*<<< orphan*/ *,int) ; 

Expr *
canonicalize_qual(Expr *qual, bool is_check)
{
	Expr	   *newqual;

	/* Quick exit for empty qual */
	if (qual == NULL)
		return NULL;

	/* This should not be invoked on quals in implicit-AND format */
	Assert(!IsA(qual, List));

	/*
	 * Pull up redundant subclauses in OR-of-AND trees.  We do this only
	 * within the top-level AND/OR structure; there's no point in looking
	 * deeper.  Also remove any NULL constants in the top-level structure.
	 */
	newqual = find_duplicate_ors(qual, is_check);

	return newqual;
}