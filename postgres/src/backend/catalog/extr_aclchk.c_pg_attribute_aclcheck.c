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
typedef  int /*<<< orphan*/  AttrNumber ;
typedef  int /*<<< orphan*/  AclResult ;
typedef  int /*<<< orphan*/  AclMode ;

/* Variables and functions */
 int /*<<< orphan*/  ACLCHECK_NO_PRIV ; 
 int /*<<< orphan*/  ACLCHECK_OK ; 
 int /*<<< orphan*/  ACLMASK_ANY ; 
 scalar_t__ pg_attribute_aclmask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

AclResult
pg_attribute_aclcheck(Oid table_oid, AttrNumber attnum,
					  Oid roleid, AclMode mode)
{
	if (pg_attribute_aclmask(table_oid, attnum, roleid, mode, ACLMASK_ANY) != 0)
		return ACLCHECK_OK;
	else
		return ACLCHECK_NO_PRIV;
}