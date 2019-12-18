#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32 ;
struct TYPE_5__ {scalar_t__* fpRelId; } ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  LOCKMODE ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ FAST_PATH_CHECK_LOCKMODE (TYPE_1__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FAST_PATH_CLEAR_LOCKMODE (TYPE_1__*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ FAST_PATH_GET_BITS (TYPE_1__*,size_t) ; 
 size_t FP_LOCK_SLOTS_PER_BACKEND ; 
 scalar_t__ FastPathLocalUseCount ; 
 TYPE_1__* MyProc ; 

__attribute__((used)) static bool
FastPathUnGrantRelationLock(Oid relid, LOCKMODE lockmode)
{
	uint32		f;
	bool		result = false;

	FastPathLocalUseCount = 0;
	for (f = 0; f < FP_LOCK_SLOTS_PER_BACKEND; f++)
	{
		if (MyProc->fpRelId[f] == relid
			&& FAST_PATH_CHECK_LOCKMODE(MyProc, f, lockmode))
		{
			Assert(!result);
			FAST_PATH_CLEAR_LOCKMODE(MyProc, f, lockmode);
			result = true;
			/* we continue iterating so as to update FastPathLocalUseCount */
		}
		if (FAST_PATH_GET_BITS(MyProc, f) != 0)
			++FastPathLocalUseCount;
	}
	return result;
}