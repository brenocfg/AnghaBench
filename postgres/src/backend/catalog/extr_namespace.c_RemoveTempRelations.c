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
struct TYPE_3__ {scalar_t__ objectSubId; int /*<<< orphan*/  objectId; int /*<<< orphan*/  classId; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ ObjectAddress ;

/* Variables and functions */
 int /*<<< orphan*/  DROP_CASCADE ; 
 int /*<<< orphan*/  NamespaceRelationId ; 
 int PERFORM_DELETION_INTERNAL ; 
 int PERFORM_DELETION_QUIETLY ; 
 int PERFORM_DELETION_SKIP_EXTENSIONS ; 
 int PERFORM_DELETION_SKIP_ORIGINAL ; 
 int /*<<< orphan*/  performDeletion (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
RemoveTempRelations(Oid tempNamespaceId)
{
	ObjectAddress object;

	/*
	 * We want to get rid of everything in the target namespace, but not the
	 * namespace itself (deleting it only to recreate it later would be a
	 * waste of cycles).  Hence, specify SKIP_ORIGINAL.  It's also an INTERNAL
	 * deletion, and we want to not drop any extensions that might happen to
	 * own temp objects.
	 */
	object.classId = NamespaceRelationId;
	object.objectId = tempNamespaceId;
	object.objectSubId = 0;

	performDeletion(&object, DROP_CASCADE,
					PERFORM_DELETION_INTERNAL |
					PERFORM_DELETION_QUIETLY |
					PERFORM_DELETION_SKIP_ORIGINAL |
					PERFORM_DELETION_SKIP_EXTENSIONS);
}