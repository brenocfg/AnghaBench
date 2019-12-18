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
typedef  int /*<<< orphan*/  uint16 ;
struct TYPE_4__ {int status; } ;
typedef  TYPE_1__ MultiXactMember ;
typedef  int /*<<< orphan*/  MultiXactId ;
typedef  scalar_t__ LockTupleMode ;

/* Variables and functions */
 int GetMultiXactIdMembers (int /*<<< orphan*/ ,TYPE_1__**,int,int) ; 
 int /*<<< orphan*/  HEAP_KEYS_UPDATED ; 
 int /*<<< orphan*/  HEAP_XMAX_EXCL_LOCK ; 
 int /*<<< orphan*/  HEAP_XMAX_IS_MULTI ; 
 int /*<<< orphan*/  HEAP_XMAX_KEYSHR_LOCK ; 
 int /*<<< orphan*/  HEAP_XMAX_LOCK_ONLY ; 
 int /*<<< orphan*/  HEAP_XMAX_SHR_LOCK ; 
 scalar_t__ LockTupleExclusive ; 
 scalar_t__ LockTupleKeyShare ; 
 scalar_t__ LockTupleNoKeyExclusive ; 
 scalar_t__ LockTupleShare ; 
#define  MultiXactStatusForKeyShare 133 
#define  MultiXactStatusForNoKeyUpdate 132 
#define  MultiXactStatusForShare 131 
#define  MultiXactStatusForUpdate 130 
#define  MultiXactStatusNoKeyUpdate 129 
#define  MultiXactStatusUpdate 128 
 scalar_t__ TUPLOCK_from_mxstatus (int) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

__attribute__((used)) static void
GetMultiXactIdHintBits(MultiXactId multi, uint16 *new_infomask,
					   uint16 *new_infomask2)
{
	int			nmembers;
	MultiXactMember *members;
	int			i;
	uint16		bits = HEAP_XMAX_IS_MULTI;
	uint16		bits2 = 0;
	bool		has_update = false;
	LockTupleMode strongest = LockTupleKeyShare;

	/*
	 * We only use this in multis we just created, so they cannot be values
	 * pre-pg_upgrade.
	 */
	nmembers = GetMultiXactIdMembers(multi, &members, false, false);

	for (i = 0; i < nmembers; i++)
	{
		LockTupleMode mode;

		/*
		 * Remember the strongest lock mode held by any member of the
		 * multixact.
		 */
		mode = TUPLOCK_from_mxstatus(members[i].status);
		if (mode > strongest)
			strongest = mode;

		/* See what other bits we need */
		switch (members[i].status)
		{
			case MultiXactStatusForKeyShare:
			case MultiXactStatusForShare:
			case MultiXactStatusForNoKeyUpdate:
				break;

			case MultiXactStatusForUpdate:
				bits2 |= HEAP_KEYS_UPDATED;
				break;

			case MultiXactStatusNoKeyUpdate:
				has_update = true;
				break;

			case MultiXactStatusUpdate:
				bits2 |= HEAP_KEYS_UPDATED;
				has_update = true;
				break;
		}
	}

	if (strongest == LockTupleExclusive ||
		strongest == LockTupleNoKeyExclusive)
		bits |= HEAP_XMAX_EXCL_LOCK;
	else if (strongest == LockTupleShare)
		bits |= HEAP_XMAX_SHR_LOCK;
	else if (strongest == LockTupleKeyShare)
		bits |= HEAP_XMAX_KEYSHR_LOCK;

	if (!has_update)
		bits |= HEAP_XMAX_LOCK_ONLY;

	if (nmembers > 0)
		pfree(members);

	*new_infomask = bits;
	*new_infomask2 = bits2;
}