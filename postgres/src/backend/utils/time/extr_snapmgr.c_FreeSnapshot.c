#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ regd_count; scalar_t__ active_count; int copied; } ;
typedef  TYPE_1__* Snapshot ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

__attribute__((used)) static void
FreeSnapshot(Snapshot snapshot)
{
	Assert(snapshot->regd_count == 0);
	Assert(snapshot->active_count == 0);
	Assert(snapshot->copied);

	pfree(snapshot);
}