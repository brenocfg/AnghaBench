#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  oid; int /*<<< orphan*/  subowner; int /*<<< orphan*/  subname; } ;
struct TYPE_6__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__* HeapTuple ;
typedef  TYPE_2__* Form_pg_subscription ;

/* Variables and functions */
 int /*<<< orphan*/  ACLCHECK_NOT_OWNER ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_PRIVILEGE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (TYPE_1__*) ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  InvokeObjectPostAlterHook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OBJECT_SUBSCRIPTION ; 
 int /*<<< orphan*/  SubscriptionRelationId ; 
 int /*<<< orphan*/  aclcheck_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  changeDependencyOnOwner (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_subscription_ownercheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  superuser_arg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
AlterSubscriptionOwner_internal(Relation rel, HeapTuple tup, Oid newOwnerId)
{
	Form_pg_subscription form;

	form = (Form_pg_subscription) GETSTRUCT(tup);

	if (form->subowner == newOwnerId)
		return;

	if (!pg_subscription_ownercheck(form->oid, GetUserId()))
		aclcheck_error(ACLCHECK_NOT_OWNER, OBJECT_SUBSCRIPTION,
					   NameStr(form->subname));

	/* New owner must be a superuser */
	if (!superuser_arg(newOwnerId))
		ereport(ERROR,
				(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
				 errmsg("permission denied to change owner of subscription \"%s\"",
						NameStr(form->subname)),
				 errhint("The owner of a subscription must be a superuser.")));

	form->subowner = newOwnerId;
	CatalogTupleUpdate(rel, &tup->t_self, tup);

	/* Update owner dependency reference */
	changeDependencyOnOwner(SubscriptionRelationId,
							form->oid,
							newOwnerId);

	InvokeObjectPostAlterHook(SubscriptionRelationId,
							  form->oid, 0);
}