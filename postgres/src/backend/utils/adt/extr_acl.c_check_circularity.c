#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ ai_grantee; int /*<<< orphan*/  ai_grantor; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  scalar_t__ AclMode ;
typedef  TYPE_1__ const AclItem ;
typedef  int /*<<< orphan*/  const Acl ;

/* Variables and functions */
 scalar_t__ ACLITEM_GET_GOPTIONS (TYPE_1__ const) ; 
 int /*<<< orphan*/  ACLMASK_ALL ; 
 TYPE_1__ const* ACL_DAT (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ACL_GRANT_OPTION_FOR (scalar_t__) ; 
 scalar_t__ ACL_ID_PUBLIC ; 
 int /*<<< orphan*/  ACL_MODECHG_DEL ; 
 scalar_t__ ACL_NO_RIGHTS ; 
 int ACL_NUM (int /*<<< orphan*/  const*) ; 
 scalar_t__ ACL_OPTION_TO_PRIVS (scalar_t__) ; 
 int /*<<< orphan*/  ACL_SIZE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DROP_CASCADE ; 
 int /*<<< orphan*/  ERRCODE_INVALID_GRANT_OPERATION ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ aclmask (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* aclupdate (int /*<<< orphan*/  const*,TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* allocacl (int) ; 
 int /*<<< orphan*/  check_acl (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
check_circularity(const Acl *old_acl, const AclItem *mod_aip,
				  Oid ownerId)
{
	Acl		   *acl;
	AclItem    *aip;
	int			i,
				num;
	AclMode		own_privs;

	check_acl(old_acl);

	/*
	 * For now, grant options can only be granted to roles, not PUBLIC.
	 * Otherwise we'd have to work a bit harder here.
	 */
	Assert(mod_aip->ai_grantee != ACL_ID_PUBLIC);

	/* The owner always has grant options, no need to check */
	if (mod_aip->ai_grantor == ownerId)
		return;

	/* Make a working copy */
	acl = allocacl(ACL_NUM(old_acl));
	memcpy(acl, old_acl, ACL_SIZE(old_acl));

	/* Zap all grant options of target grantee, plus what depends on 'em */
cc_restart:
	num = ACL_NUM(acl);
	aip = ACL_DAT(acl);
	for (i = 0; i < num; i++)
	{
		if (aip[i].ai_grantee == mod_aip->ai_grantee &&
			ACLITEM_GET_GOPTIONS(aip[i]) != ACL_NO_RIGHTS)
		{
			Acl		   *new_acl;

			/* We'll actually zap ordinary privs too, but no matter */
			new_acl = aclupdate(acl, &aip[i], ACL_MODECHG_DEL,
								ownerId, DROP_CASCADE);

			pfree(acl);
			acl = new_acl;

			goto cc_restart;
		}
	}

	/* Now we can compute grantor's independently-derived privileges */
	own_privs = aclmask(acl,
						mod_aip->ai_grantor,
						ownerId,
						ACL_GRANT_OPTION_FOR(ACLITEM_GET_GOPTIONS(*mod_aip)),
						ACLMASK_ALL);
	own_privs = ACL_OPTION_TO_PRIVS(own_privs);

	if ((ACLITEM_GET_GOPTIONS(*mod_aip) & ~own_privs) != 0)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_GRANT_OPERATION),
				 errmsg("grant options cannot be granted back to your own grantor")));

	pfree(acl);
}