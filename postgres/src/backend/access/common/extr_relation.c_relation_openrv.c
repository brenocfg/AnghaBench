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
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  RangeVar ;
typedef  int /*<<< orphan*/  Oid ;
typedef  scalar_t__ LOCKMODE ;

/* Variables and functions */
 int /*<<< orphan*/  AcceptInvalidationMessages () ; 
 scalar_t__ NoLock ; 
 int /*<<< orphan*/  RangeVarGetRelid (int /*<<< orphan*/  const*,scalar_t__,int) ; 
 int /*<<< orphan*/  relation_open (int /*<<< orphan*/ ,scalar_t__) ; 

Relation
relation_openrv(const RangeVar *relation, LOCKMODE lockmode)
{
	Oid			relOid;

	/*
	 * Check for shared-cache-inval messages before trying to open the
	 * relation.  This is needed even if we already hold a lock on the
	 * relation, because GRANT/REVOKE are executed without taking any lock on
	 * the target relation, and we want to be sure we see current ACL
	 * information.  We can skip this if asked for NoLock, on the assumption
	 * that such a call is not the first one in the current command, and so we
	 * should be reasonably up-to-date already.  (XXX this all could stand to
	 * be redesigned, but for the moment we'll keep doing this like it's been
	 * done historically.)
	 */
	if (lockmode != NoLock)
		AcceptInvalidationMessages();

	/* Look up and lock the appropriate relation using namespace search */
	relOid = RangeVarGetRelid(relation, lockmode, false);

	/* Let relation_open do the rest */
	return relation_open(relOid, NoLock);
}