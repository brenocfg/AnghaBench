#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  relname; int /*<<< orphan*/  nspname; } ;
struct TYPE_5__ {TYPE_1__ remoterel; int /*<<< orphan*/  localrel; scalar_t__ updatable; } ;
typedef  TYPE_2__ LogicalRepRelMapEntry ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetRelationIdentityOrPK (int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_relation_updatable(LogicalRepRelMapEntry *rel)
{
	/* Updatable, no error. */
	if (rel->updatable)
		return;

	/*
	 * We are in error mode so it's fine this is somewhat slow. It's better to
	 * give user correct error.
	 */
	if (OidIsValid(GetRelationIdentityOrPK(rel->localrel)))
	{
		ereport(ERROR,
				(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
				 errmsg("publisher did not send replica identity column "
						"expected by the logical replication target relation \"%s.%s\"",
						rel->remoterel.nspname, rel->remoterel.relname)));
	}

	ereport(ERROR,
			(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
			 errmsg("logical replication target relation \"%s.%s\" has "
					"neither REPLICA IDENTITY index nor PRIMARY "
					"KEY and published relation does not have "
					"REPLICA IDENTITY FULL",
					rel->remoterel.nspname, rel->remoterel.relname)));
}