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
struct TYPE_3__ {int ereport_on_violation; int result; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ ObjectAccessNamespaceSearch ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NamespaceRelationId ; 
 int /*<<< orphan*/  OAT_NAMESPACE_SEARCH ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  object_access_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

bool
RunNamespaceSearchHook(Oid objectId, bool ereport_on_violation)
{
	ObjectAccessNamespaceSearch ns_arg;

	/* caller should check, but just in case... */
	Assert(object_access_hook != NULL);

	memset(&ns_arg, 0, sizeof(ObjectAccessNamespaceSearch));
	ns_arg.ereport_on_violation = ereport_on_violation;
	ns_arg.result = true;

	(*object_access_hook) (OAT_NAMESPACE_SEARCH,
						   NamespaceRelationId, objectId, 0,
						   (void *) &ns_arg);

	return ns_arg.result;
}