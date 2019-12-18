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
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  LOCKTAG ;
typedef  int /*<<< orphan*/  LOCKMODE ;

/* Variables and functions */
 int /*<<< orphan*/  LockRelease (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SetLocktagRelationOid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
UnlockRelationOid(Oid relid, LOCKMODE lockmode)
{
	LOCKTAG		tag;

	SetLocktagRelationOid(&tag, relid);

	LockRelease(&tag, lockmode, false);
}