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
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  AuthIdRelationId ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  SHARED_DEPENDENCY_ACL ; 
 int /*<<< orphan*/  SHARED_DEPENDENCY_OWNER ; 
 int /*<<< orphan*/  SharedDependRelationId ; 
 int /*<<< orphan*/  shdepChangeDep (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shdepDropDependency (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
changeDependencyOnOwner(Oid classId, Oid objectId, Oid newOwnerId)
{
	Relation	sdepRel;

	sdepRel = table_open(SharedDependRelationId, RowExclusiveLock);

	/* Adjust the SHARED_DEPENDENCY_OWNER entry */
	shdepChangeDep(sdepRel,
				   classId, objectId, 0,
				   AuthIdRelationId, newOwnerId,
				   SHARED_DEPENDENCY_OWNER);

	/*----------
	 * There should never be a SHARED_DEPENDENCY_ACL entry for the owner,
	 * so get rid of it if there is one.  This can happen if the new owner
	 * was previously granted some rights to the object.
	 *
	 * This step is analogous to aclnewowner's removal of duplicate entries
	 * in the ACL.  We have to do it to handle this scenario:
	 *		A grants some rights on an object to B
	 *		ALTER OWNER changes the object's owner to B
	 *		ALTER OWNER changes the object's owner to C
	 * The third step would remove all mention of B from the object's ACL,
	 * but we'd still have a SHARED_DEPENDENCY_ACL for B if we did not do
	 * things this way.
	 *
	 * The rule against having a SHARED_DEPENDENCY_ACL entry for the owner
	 * allows us to fix things up in just this one place, without having
	 * to make the various ALTER OWNER routines each know about it.
	 *----------
	 */
	shdepDropDependency(sdepRel, classId, objectId, 0, true,
						AuthIdRelationId, newOwnerId,
						SHARED_DEPENDENCY_ACL);

	table_close(sdepRel, RowExclusiveLock);
}