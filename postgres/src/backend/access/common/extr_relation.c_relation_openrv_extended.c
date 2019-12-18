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
typedef  int /*<<< orphan*/ * Relation ;
typedef  int /*<<< orphan*/  RangeVar ;
typedef  int /*<<< orphan*/  Oid ;
typedef  scalar_t__ LOCKMODE ;

/* Variables and functions */
 int /*<<< orphan*/  AcceptInvalidationMessages () ; 
 scalar_t__ NoLock ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RangeVarGetRelid (int /*<<< orphan*/  const*,scalar_t__,int) ; 
 int /*<<< orphan*/ * relation_open (int /*<<< orphan*/ ,scalar_t__) ; 

Relation
relation_openrv_extended(const RangeVar *relation, LOCKMODE lockmode,
						 bool missing_ok)
{
	Oid			relOid;

	/*
	 * Check for shared-cache-inval messages before trying to open the
	 * relation.  See comments in relation_openrv().
	 */
	if (lockmode != NoLock)
		AcceptInvalidationMessages();

	/* Look up and lock the appropriate relation using namespace search */
	relOid = RangeVarGetRelid(relation, lockmode, missing_ok);

	/* Return NULL on not-found */
	if (!OidIsValid(relOid))
		return NULL;

	/* Let relation_open do the rest */
	return relation_open(relOid, NoLock);
}