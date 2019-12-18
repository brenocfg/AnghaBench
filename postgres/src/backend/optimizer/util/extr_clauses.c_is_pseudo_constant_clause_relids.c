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
typedef  int /*<<< orphan*/  Relids ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 scalar_t__ bms_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  contain_volatile_functions (int /*<<< orphan*/ *) ; 

bool
is_pseudo_constant_clause_relids(Node *clause, Relids relids)
{
	if (bms_is_empty(relids) &&
		!contain_volatile_functions(clause))
		return true;
	return false;
}