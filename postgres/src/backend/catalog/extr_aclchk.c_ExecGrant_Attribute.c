#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  values ;
typedef  int /*<<< orphan*/  replaces ;
typedef  int /*<<< orphan*/  nulls ;
struct TYPE_15__ {int /*<<< orphan*/  attname; } ;
struct TYPE_14__ {int /*<<< orphan*/  t_self; } ;
struct TYPE_13__ {int /*<<< orphan*/  grantees; int /*<<< orphan*/  behavior; int /*<<< orphan*/  grant_option; int /*<<< orphan*/  is_grant; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ InternalGrant ;
typedef  TYPE_2__* HeapTuple ;
typedef  TYPE_3__* Form_pg_attribute ;
typedef  int Datum ;
typedef  int /*<<< orphan*/  AttrNumber ;
typedef  int /*<<< orphan*/  AclMode ;
typedef  int /*<<< orphan*/  Acl ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_ALL_RIGHTS_COLUMN ; 
 scalar_t__ ACL_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ATTNUM ; 
 int Anum_pg_attribute_attacl ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * DatumGetAclPCopy (int) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (TYPE_2__*) ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_2__*) ; 
 int /*<<< orphan*/  Int16GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemSet (int*,int,int) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int Natts_pg_attribute ; 
 int /*<<< orphan*/  OBJECT_COLUMN ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationRelationId ; 
 int /*<<< orphan*/  ReleaseSysCache (TYPE_2__*) ; 
 TYPE_2__* SearchSysCache2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SysCacheGetAttr (int /*<<< orphan*/ ,TYPE_2__*,int,int*) ; 
 int /*<<< orphan*/ * aclconcat (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * acldefault (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int aclmembers (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* heap_modify_tuple (TYPE_2__*,int /*<<< orphan*/ ,int*,int*,int*) ; 
 int /*<<< orphan*/ * merge_acl_with_grant (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  recordExtensionInitPriv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  restrict_and_check_grant (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  select_best_grantor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  updateAclDependencies (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ExecGrant_Attribute(InternalGrant *istmt, Oid relOid, const char *relname,
					AttrNumber attnum, Oid ownerId, AclMode col_privileges,
					Relation attRelation, const Acl *old_rel_acl)
{
	HeapTuple	attr_tuple;
	Form_pg_attribute pg_attribute_tuple;
	Acl		   *old_acl;
	Acl		   *new_acl;
	Acl		   *merged_acl;
	Datum		aclDatum;
	bool		isNull;
	Oid			grantorId;
	AclMode		avail_goptions;
	bool		need_update;
	HeapTuple	newtuple;
	Datum		values[Natts_pg_attribute];
	bool		nulls[Natts_pg_attribute];
	bool		replaces[Natts_pg_attribute];
	int			noldmembers;
	int			nnewmembers;
	Oid		   *oldmembers;
	Oid		   *newmembers;

	attr_tuple = SearchSysCache2(ATTNUM,
								 ObjectIdGetDatum(relOid),
								 Int16GetDatum(attnum));
	if (!HeapTupleIsValid(attr_tuple))
		elog(ERROR, "cache lookup failed for attribute %d of relation %u",
			 attnum, relOid);
	pg_attribute_tuple = (Form_pg_attribute) GETSTRUCT(attr_tuple);

	/*
	 * Get working copy of existing ACL. If there's no ACL, substitute the
	 * proper default.
	 */
	aclDatum = SysCacheGetAttr(ATTNUM, attr_tuple, Anum_pg_attribute_attacl,
							   &isNull);
	if (isNull)
	{
		old_acl = acldefault(OBJECT_COLUMN, ownerId);
		/* There are no old member roles according to the catalogs */
		noldmembers = 0;
		oldmembers = NULL;
	}
	else
	{
		old_acl = DatumGetAclPCopy(aclDatum);
		/* Get the roles mentioned in the existing ACL */
		noldmembers = aclmembers(old_acl, &oldmembers);
	}

	/*
	 * In select_best_grantor we should consider existing table-level ACL bits
	 * as well as the per-column ACL.  Build a new ACL that is their
	 * concatenation.  (This is a bit cheap and dirty compared to merging them
	 * properly with no duplications, but it's all we need here.)
	 */
	merged_acl = aclconcat(old_rel_acl, old_acl);

	/* Determine ID to do the grant as, and available grant options */
	select_best_grantor(GetUserId(), col_privileges,
						merged_acl, ownerId,
						&grantorId, &avail_goptions);

	pfree(merged_acl);

	/*
	 * Restrict the privileges to what we can actually grant, and emit the
	 * standards-mandated warning and error messages.  Note: we don't track
	 * whether the user actually used the ALL PRIVILEGES(columns) syntax for
	 * each column; we just approximate it by whether all the possible
	 * privileges are specified now.  Since the all_privs flag only determines
	 * whether a warning is issued, this seems close enough.
	 */
	col_privileges =
		restrict_and_check_grant(istmt->is_grant, avail_goptions,
								 (col_privileges == ACL_ALL_RIGHTS_COLUMN),
								 col_privileges,
								 relOid, grantorId, OBJECT_COLUMN,
								 relname, attnum,
								 NameStr(pg_attribute_tuple->attname));

	/*
	 * Generate new ACL.
	 */
	new_acl = merge_acl_with_grant(old_acl, istmt->is_grant,
								   istmt->grant_option,
								   istmt->behavior, istmt->grantees,
								   col_privileges, grantorId,
								   ownerId);

	/*
	 * We need the members of both old and new ACLs so we can correct the
	 * shared dependency information.
	 */
	nnewmembers = aclmembers(new_acl, &newmembers);

	/* finished building new ACL value, now insert it */
	MemSet(values, 0, sizeof(values));
	MemSet(nulls, false, sizeof(nulls));
	MemSet(replaces, false, sizeof(replaces));

	/*
	 * If the updated ACL is empty, we can set attacl to null, and maybe even
	 * avoid an update of the pg_attribute row.  This is worth testing because
	 * we'll come through here multiple times for any relation-level REVOKE,
	 * even if there were never any column GRANTs.  Note we are assuming that
	 * the "default" ACL state for columns is empty.
	 */
	if (ACL_NUM(new_acl) > 0)
	{
		values[Anum_pg_attribute_attacl - 1] = PointerGetDatum(new_acl);
		need_update = true;
	}
	else
	{
		nulls[Anum_pg_attribute_attacl - 1] = true;
		need_update = !isNull;
	}
	replaces[Anum_pg_attribute_attacl - 1] = true;

	if (need_update)
	{
		newtuple = heap_modify_tuple(attr_tuple, RelationGetDescr(attRelation),
									 values, nulls, replaces);

		CatalogTupleUpdate(attRelation, &newtuple->t_self, newtuple);

		/* Update initial privileges for extensions */
		recordExtensionInitPriv(relOid, RelationRelationId, attnum,
								ACL_NUM(new_acl) > 0 ? new_acl : NULL);

		/* Update the shared dependency ACL info */
		updateAclDependencies(RelationRelationId, relOid, attnum,
							  ownerId,
							  noldmembers, oldmembers,
							  nnewmembers, newmembers);
	}

	pfree(new_acl);

	ReleaseSysCache(attr_tuple);
}