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
typedef  int /*<<< orphan*/  CreateEventTrigStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eventname ; 
 int /*<<< orphan*/  funcname ; 
 int /*<<< orphan*/  trigname ; 
 int /*<<< orphan*/  whenclause ; 

__attribute__((used)) static bool
_equalCreateEventTrigStmt(const CreateEventTrigStmt *a, const CreateEventTrigStmt *b)
{
	COMPARE_STRING_FIELD(trigname);
	COMPARE_STRING_FIELD(eventname);
	COMPARE_NODE_FIELD(whenclause);
	COMPARE_NODE_FIELD(funcname);

	return true;
}