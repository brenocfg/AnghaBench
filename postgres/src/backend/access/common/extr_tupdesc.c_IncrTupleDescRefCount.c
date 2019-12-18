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
typedef  TYPE_1__* TupleDesc ;
struct TYPE_4__ {scalar_t__ tdrefcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CurrentResourceOwner ; 
 int /*<<< orphan*/  ResourceOwnerEnlargeTupleDescs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResourceOwnerRememberTupleDesc (int /*<<< orphan*/ ,TYPE_1__*) ; 

void
IncrTupleDescRefCount(TupleDesc tupdesc)
{
	Assert(tupdesc->tdrefcount >= 0);

	ResourceOwnerEnlargeTupleDescs(CurrentResourceOwner);
	tupdesc->tdrefcount++;
	ResourceOwnerRememberTupleDesc(CurrentResourceOwner, tupdesc);
}