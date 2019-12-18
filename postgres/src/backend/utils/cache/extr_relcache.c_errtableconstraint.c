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
typedef  int /*<<< orphan*/  Relation ;

/* Variables and functions */
 int /*<<< orphan*/  PG_DIAG_CONSTRAINT_NAME ; 
 int /*<<< orphan*/  err_generic_string (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  errtable (int /*<<< orphan*/ ) ; 

int
errtableconstraint(Relation rel, const char *conname)
{
	errtable(rel);
	err_generic_string(PG_DIAG_CONSTRAINT_NAME, conname);

	return 0;					/* return value does not matter */
}