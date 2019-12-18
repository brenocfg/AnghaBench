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
typedef  scalar_t__ LOCKMODE ;
typedef  int /*<<< orphan*/  AclResult ;
typedef  int AclMode ;

/* Variables and functions */
 int ACL_DELETE ; 
 int ACL_INSERT ; 
 int ACL_SELECT ; 
 int ACL_TRUNCATE ; 
 int ACL_UPDATE ; 
 scalar_t__ AccessShareLock ; 
 scalar_t__ RowExclusiveLock ; 
 int /*<<< orphan*/  pg_class_aclcheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static AclResult
LockTableAclCheck(Oid reloid, LOCKMODE lockmode, Oid userid)
{
	AclResult	aclresult;
	AclMode		aclmask;

	/* Verify adequate privilege */
	if (lockmode == AccessShareLock)
		aclmask = ACL_SELECT;
	else if (lockmode == RowExclusiveLock)
		aclmask = ACL_INSERT | ACL_UPDATE | ACL_DELETE | ACL_TRUNCATE;
	else
		aclmask = ACL_UPDATE | ACL_DELETE | ACL_TRUNCATE;

	aclresult = pg_class_aclcheck(reloid, userid, aclmask);

	return aclresult;
}