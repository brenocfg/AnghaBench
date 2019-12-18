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
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_3__ {int /*<<< orphan*/  refcount; } ;
typedef  TYPE_1__ PrivateRefCountEntry ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BufferIsLocal (int /*<<< orphan*/ ) ; 
 int BufferIsValid (int /*<<< orphan*/ ) ; 
 TYPE_1__* GetPrivateRefCountEntry (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int32
GetPrivateRefCount(Buffer buffer)
{
	PrivateRefCountEntry *ref;

	Assert(BufferIsValid(buffer));
	Assert(!BufferIsLocal(buffer));

	/*
	 * Not moving the entry - that's ok for the current users, but we might
	 * want to change this one day.
	 */
	ref = GetPrivateRefCountEntry(buffer, false);

	if (ref == NULL)
		return 0;
	return ref->refcount;
}