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
struct TYPE_3__ {scalar_t__ ri_FdwState; } ;
typedef  TYPE_1__ ResultRelInfo ;
typedef  int /*<<< orphan*/  PgFdwModifyState ;
typedef  int /*<<< orphan*/  EState ;

/* Variables and functions */
 int /*<<< orphan*/  finish_foreign_modify (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
postgresEndForeignModify(EState *estate,
						 ResultRelInfo *resultRelInfo)
{
	PgFdwModifyState *fmstate = (PgFdwModifyState *) resultRelInfo->ri_FdwState;

	/* If fmstate is NULL, we are in EXPLAIN; nothing to do */
	if (fmstate == NULL)
		return;

	/* Destroy the execution state */
	finish_foreign_modify(fmstate);
}