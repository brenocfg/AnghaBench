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
struct TYPE_3__ {int /*<<< orphan*/  locktag_lockmethodid; } ;
typedef  int /*<<< orphan*/  LockMethod ;
typedef  TYPE_1__ LOCKTAG ;
typedef  size_t LOCKMETHODID ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ * LockMethods ; 
 size_t lengthof (int /*<<< orphan*/ *) ; 

LockMethod
GetLockTagsMethodTable(const LOCKTAG *locktag)
{
	LOCKMETHODID lockmethodid = (LOCKMETHODID) locktag->locktag_lockmethodid;

	Assert(0 < lockmethodid && lockmethodid < lengthof(LockMethods));
	return LockMethods[lockmethodid];
}