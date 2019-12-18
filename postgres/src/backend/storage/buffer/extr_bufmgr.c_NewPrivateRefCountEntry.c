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
struct TYPE_4__ {scalar_t__ refcount; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ PrivateRefCountEntry ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* ReservedRefCountEntry ; 

__attribute__((used)) static PrivateRefCountEntry *
NewPrivateRefCountEntry(Buffer buffer)
{
	PrivateRefCountEntry *res;

	/* only allowed to be called when a reservation has been made */
	Assert(ReservedRefCountEntry != NULL);

	/* use up the reserved entry */
	res = ReservedRefCountEntry;
	ReservedRefCountEntry = NULL;

	/* and fill it */
	res->buffer = buffer;
	res->refcount = 0;

	return res;
}