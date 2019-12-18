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
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_2__ {scalar_t__ condeferrable; scalar_t__ condeferred; } ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_constraint ;

/* Variables and functions */
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decompile_conbin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
constraints_equivalent(HeapTuple a, HeapTuple b, TupleDesc tupleDesc)
{
	Form_pg_constraint acon = (Form_pg_constraint) GETSTRUCT(a);
	Form_pg_constraint bcon = (Form_pg_constraint) GETSTRUCT(b);

	if (acon->condeferrable != bcon->condeferrable ||
		acon->condeferred != bcon->condeferred ||
		strcmp(decompile_conbin(a, tupleDesc),
			   decompile_conbin(b, tupleDesc)) != 0)
		return false;
	else
		return true;
}