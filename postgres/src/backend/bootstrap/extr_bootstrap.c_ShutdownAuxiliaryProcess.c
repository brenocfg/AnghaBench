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
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ConditionVariableCancelSleep () ; 
 int /*<<< orphan*/  LWLockReleaseAll () ; 
 int /*<<< orphan*/  pgstat_report_wait_end () ; 

__attribute__((used)) static void
ShutdownAuxiliaryProcess(int code, Datum arg)
{
	LWLockReleaseAll();
	ConditionVariableCancelSleep();
	pgstat_report_wait_end();
}