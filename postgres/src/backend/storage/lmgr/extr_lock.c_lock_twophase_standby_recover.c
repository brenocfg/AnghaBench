#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
typedef  int /*<<< orphan*/  uint16 ;
struct TYPE_4__ {scalar_t__ locktag_lockmethodid; scalar_t__ locktag_type; int /*<<< orphan*/  locktag_field2; int /*<<< orphan*/  locktag_field1; } ;
struct TYPE_3__ {scalar_t__ lockmode; TYPE_2__ locktag; } ;
typedef  TYPE_1__ TwoPhaseLockRecord ;
typedef  int /*<<< orphan*/  TransactionId ;
typedef  TYPE_2__ LOCKTAG ;
typedef  scalar_t__ LOCKMODE ;
typedef  scalar_t__ LOCKMETHODID ;

/* Variables and functions */
 scalar_t__ AccessExclusiveLock ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ LOCKTAG_RELATION ; 
 int /*<<< orphan*/  LockMethods ; 
 int /*<<< orphan*/  StandbyAcquireAccessExclusiveLock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ lengthof (int /*<<< orphan*/ ) ; 

void
lock_twophase_standby_recover(TransactionId xid, uint16 info,
							  void *recdata, uint32 len)
{
	TwoPhaseLockRecord *rec = (TwoPhaseLockRecord *) recdata;
	LOCKTAG    *locktag;
	LOCKMODE	lockmode;
	LOCKMETHODID lockmethodid;

	Assert(len == sizeof(TwoPhaseLockRecord));
	locktag = &rec->locktag;
	lockmode = rec->lockmode;
	lockmethodid = locktag->locktag_lockmethodid;

	if (lockmethodid <= 0 || lockmethodid >= lengthof(LockMethods))
		elog(ERROR, "unrecognized lock method: %d", lockmethodid);

	if (lockmode == AccessExclusiveLock &&
		locktag->locktag_type == LOCKTAG_RELATION)
	{
		StandbyAcquireAccessExclusiveLock(xid,
										  locktag->locktag_field1 /* dboid */ ,
										  locktag->locktag_field2 /* reloid */ );
	}
}