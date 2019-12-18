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
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  DEPENDENCY_INTERNAL ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * getOwnedSequences_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linitial_oid (int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ *) ; 

Oid
getIdentitySequence(Oid relid, AttrNumber attnum, bool missing_ok)
{
	List	   *seqlist = getOwnedSequences_internal(relid, attnum, DEPENDENCY_INTERNAL);

	if (list_length(seqlist) > 1)
		elog(ERROR, "more than one owned sequence found");
	else if (list_length(seqlist) < 1)
	{
		if (missing_ok)
			return InvalidOid;
		else
			elog(ERROR, "no owned sequence found");
	}

	return linitial_oid(seqlist);
}