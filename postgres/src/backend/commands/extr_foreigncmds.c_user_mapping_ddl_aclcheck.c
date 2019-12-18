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
typedef  scalar_t__ Oid ;
typedef  scalar_t__ AclResult ;

/* Variables and functions */
 scalar_t__ ACLCHECK_NOT_OWNER ; 
 scalar_t__ ACLCHECK_OK ; 
 int /*<<< orphan*/  ACL_USAGE ; 
 scalar_t__ GetUserId () ; 
 int /*<<< orphan*/  OBJECT_FOREIGN_SERVER ; 
 int /*<<< orphan*/  aclcheck_error (scalar_t__,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ pg_foreign_server_aclcheck (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_foreign_server_ownercheck (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
user_mapping_ddl_aclcheck(Oid umuserid, Oid serverid, const char *servername)
{
	Oid			curuserid = GetUserId();

	if (!pg_foreign_server_ownercheck(serverid, curuserid))
	{
		if (umuserid == curuserid)
		{
			AclResult	aclresult;

			aclresult = pg_foreign_server_aclcheck(serverid, curuserid, ACL_USAGE);
			if (aclresult != ACLCHECK_OK)
				aclcheck_error(aclresult, OBJECT_FOREIGN_SERVER, servername);
		}
		else
			aclcheck_error(ACLCHECK_NOT_OWNER, OBJECT_FOREIGN_SERVER,
						   servername);
	}
}