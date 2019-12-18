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
struct TYPE_2__ {int /*<<< orphan*/  oldestMultiXactId; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  MultiXactId ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InRecovery ; 
 scalar_t__ MultiXactIdPrecedes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* MultiXactState ; 
 int /*<<< orphan*/  SetMultiXactIdLimit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
MultiXactAdvanceOldest(MultiXactId oldestMulti, Oid oldestMultiDB)
{
	Assert(InRecovery);

	if (MultiXactIdPrecedes(MultiXactState->oldestMultiXactId, oldestMulti))
		SetMultiXactIdLimit(oldestMulti, oldestMultiDB, false);
}