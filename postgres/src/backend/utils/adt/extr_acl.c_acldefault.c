#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* ai_grantor; void* ai_grantee; } ;
typedef  void* Oid ;
typedef  int ObjectType ;
typedef  scalar_t__ AclMode ;
typedef  TYPE_1__ AclItem ;
typedef  int /*<<< orphan*/  Acl ;

/* Variables and functions */
 int /*<<< orphan*/  ACLITEM_SET_PRIVS_GOPTIONS (TYPE_1__,scalar_t__,scalar_t__) ; 
 scalar_t__ ACL_ALL_RIGHTS_DATABASE ; 
 scalar_t__ ACL_ALL_RIGHTS_FDW ; 
 scalar_t__ ACL_ALL_RIGHTS_FOREIGN_SERVER ; 
 scalar_t__ ACL_ALL_RIGHTS_FUNCTION ; 
 scalar_t__ ACL_ALL_RIGHTS_LANGUAGE ; 
 scalar_t__ ACL_ALL_RIGHTS_LARGEOBJECT ; 
 scalar_t__ ACL_ALL_RIGHTS_RELATION ; 
 scalar_t__ ACL_ALL_RIGHTS_SCHEMA ; 
 scalar_t__ ACL_ALL_RIGHTS_SEQUENCE ; 
 scalar_t__ ACL_ALL_RIGHTS_TABLESPACE ; 
 scalar_t__ ACL_ALL_RIGHTS_TYPE ; 
 scalar_t__ ACL_CONNECT ; 
 scalar_t__ ACL_CREATE_TEMP ; 
 TYPE_1__* ACL_DAT (int /*<<< orphan*/ *) ; 
 scalar_t__ ACL_EXECUTE ; 
 void* ACL_ID_PUBLIC ; 
 scalar_t__ ACL_NO_RIGHTS ; 
 scalar_t__ ACL_USAGE ; 
 int /*<<< orphan*/  ERROR ; 
#define  OBJECT_COLUMN 140 
#define  OBJECT_DATABASE 139 
#define  OBJECT_DOMAIN 138 
#define  OBJECT_FDW 137 
#define  OBJECT_FOREIGN_SERVER 136 
#define  OBJECT_FUNCTION 135 
#define  OBJECT_LANGUAGE 134 
#define  OBJECT_LARGEOBJECT 133 
#define  OBJECT_SCHEMA 132 
#define  OBJECT_SEQUENCE 131 
#define  OBJECT_TABLE 130 
#define  OBJECT_TABLESPACE 129 
#define  OBJECT_TYPE 128 
 int /*<<< orphan*/ * allocacl (int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 

Acl *
acldefault(ObjectType objtype, Oid ownerId)
{
	AclMode		world_default;
	AclMode		owner_default;
	int			nacl;
	Acl		   *acl;
	AclItem    *aip;

	switch (objtype)
	{
		case OBJECT_COLUMN:
			/* by default, columns have no extra privileges */
			world_default = ACL_NO_RIGHTS;
			owner_default = ACL_NO_RIGHTS;
			break;
		case OBJECT_TABLE:
			world_default = ACL_NO_RIGHTS;
			owner_default = ACL_ALL_RIGHTS_RELATION;
			break;
		case OBJECT_SEQUENCE:
			world_default = ACL_NO_RIGHTS;
			owner_default = ACL_ALL_RIGHTS_SEQUENCE;
			break;
		case OBJECT_DATABASE:
			/* for backwards compatibility, grant some rights by default */
			world_default = ACL_CREATE_TEMP | ACL_CONNECT;
			owner_default = ACL_ALL_RIGHTS_DATABASE;
			break;
		case OBJECT_FUNCTION:
			/* Grant EXECUTE by default, for now */
			world_default = ACL_EXECUTE;
			owner_default = ACL_ALL_RIGHTS_FUNCTION;
			break;
		case OBJECT_LANGUAGE:
			/* Grant USAGE by default, for now */
			world_default = ACL_USAGE;
			owner_default = ACL_ALL_RIGHTS_LANGUAGE;
			break;
		case OBJECT_LARGEOBJECT:
			world_default = ACL_NO_RIGHTS;
			owner_default = ACL_ALL_RIGHTS_LARGEOBJECT;
			break;
		case OBJECT_SCHEMA:
			world_default = ACL_NO_RIGHTS;
			owner_default = ACL_ALL_RIGHTS_SCHEMA;
			break;
		case OBJECT_TABLESPACE:
			world_default = ACL_NO_RIGHTS;
			owner_default = ACL_ALL_RIGHTS_TABLESPACE;
			break;
		case OBJECT_FDW:
			world_default = ACL_NO_RIGHTS;
			owner_default = ACL_ALL_RIGHTS_FDW;
			break;
		case OBJECT_FOREIGN_SERVER:
			world_default = ACL_NO_RIGHTS;
			owner_default = ACL_ALL_RIGHTS_FOREIGN_SERVER;
			break;
		case OBJECT_DOMAIN:
		case OBJECT_TYPE:
			world_default = ACL_USAGE;
			owner_default = ACL_ALL_RIGHTS_TYPE;
			break;
		default:
			elog(ERROR, "unrecognized objtype: %d", (int) objtype);
			world_default = ACL_NO_RIGHTS;	/* keep compiler quiet */
			owner_default = ACL_NO_RIGHTS;
			break;
	}

	nacl = 0;
	if (world_default != ACL_NO_RIGHTS)
		nacl++;
	if (owner_default != ACL_NO_RIGHTS)
		nacl++;

	acl = allocacl(nacl);
	aip = ACL_DAT(acl);

	if (world_default != ACL_NO_RIGHTS)
	{
		aip->ai_grantee = ACL_ID_PUBLIC;
		aip->ai_grantor = ownerId;
		ACLITEM_SET_PRIVS_GOPTIONS(*aip, world_default, ACL_NO_RIGHTS);
		aip++;
	}

	/*
	 * Note that the owner's entry shows all ordinary privileges but no grant
	 * options.  This is because his grant options come "from the system" and
	 * not from his own efforts.  (The SQL spec says that the owner's rights
	 * come from a "_SYSTEM" authid.)  However, we do consider that the
	 * owner's ordinary privileges are self-granted; this lets him revoke
	 * them.  We implement the owner's grant options without any explicit
	 * "_SYSTEM"-like ACL entry, by internally special-casing the owner
	 * wherever we are testing grant options.
	 */
	if (owner_default != ACL_NO_RIGHTS)
	{
		aip->ai_grantee = ownerId;
		aip->ai_grantor = ownerId;
		ACLITEM_SET_PRIVS_GOPTIONS(*aip, owner_default, ACL_NO_RIGHTS);
	}

	return acl;
}