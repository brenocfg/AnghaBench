#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  values ;
typedef  int /*<<< orphan*/  replaces ;
typedef  int /*<<< orphan*/  nulls ;
struct TYPE_22__ {int /*<<< orphan*/  oid; } ;
struct TYPE_21__ {int /*<<< orphan*/  t_self; } ;
struct TYPE_20__ {int objtype; int /*<<< orphan*/  roleid; int /*<<< orphan*/  nspid; int /*<<< orphan*/  grantees; int /*<<< orphan*/  behavior; int /*<<< orphan*/  grant_option; int /*<<< orphan*/  is_grant; int /*<<< orphan*/  all_privs; int /*<<< orphan*/  privileges; } ;
struct TYPE_19__ {scalar_t__ objectSubId; int /*<<< orphan*/  objectId; void* classId; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ ObjectAddress ;
typedef  TYPE_2__ InternalDefaultACL ;
typedef  TYPE_3__* HeapTuple ;
typedef  TYPE_4__* Form_pg_default_acl ;
typedef  int Datum ;
typedef  int /*<<< orphan*/  AclMode ;
typedef  int /*<<< orphan*/  Acl ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_ALL_RIGHTS_FUNCTION ; 
 int /*<<< orphan*/  ACL_ALL_RIGHTS_RELATION ; 
 int /*<<< orphan*/  ACL_ALL_RIGHTS_SCHEMA ; 
 int /*<<< orphan*/  ACL_ALL_RIGHTS_SEQUENCE ; 
 int /*<<< orphan*/  ACL_ALL_RIGHTS_TYPE ; 
 int /*<<< orphan*/  ACL_NO_RIGHTS ; 
 int Anum_pg_default_acl_defaclacl ; 
 int Anum_pg_default_acl_defaclnamespace ; 
 int Anum_pg_default_acl_defaclobjtype ; 
 int Anum_pg_default_acl_defaclrole ; 
 int Anum_pg_default_acl_oid ; 
 int /*<<< orphan*/  CatalogTupleInsert (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int CharGetDatum (char) ; 
 char DEFACLOBJ_FUNCTION ; 
 char DEFACLOBJ_NAMESPACE ; 
 char DEFACLOBJ_RELATION ; 
 char DEFACLOBJ_SEQUENCE ; 
 char DEFACLOBJ_TYPE ; 
 int /*<<< orphan*/  DEFACLROLENSPOBJ ; 
 int /*<<< orphan*/  DEPENDENCY_AUTO ; 
 int /*<<< orphan*/  DROP_RESTRICT ; 
 int /*<<< orphan*/ * DatumGetAclPCopy (int) ; 
 int /*<<< orphan*/  DefaultAclOidIndexId ; 
 void* DefaultAclRelationId ; 
 int /*<<< orphan*/  ERRCODE_INVALID_GRANT_OPERATION ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (TYPE_3__*) ; 
 int /*<<< orphan*/  GetNewOidWithIndex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ HeapTupleIsValid (TYPE_3__*) ; 
 int /*<<< orphan*/  InvokeObjectPostAlterHook (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvokeObjectPostCreateHook (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemSet (int*,int,int) ; 
 void* NamespaceRelationId ; 
 int Natts_pg_default_acl ; 
#define  OBJECT_FUNCTION 132 
#define  OBJECT_SCHEMA 131 
#define  OBJECT_SEQUENCE 130 
#define  OBJECT_TABLE 129 
#define  OBJECT_TYPE 128 
 int ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (TYPE_3__*) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 TYPE_3__* SearchSysCache3 (int /*<<< orphan*/ ,int,int,int) ; 
 int SysCacheGetAttr (int /*<<< orphan*/ ,TYPE_3__*,int,int*) ; 
 int /*<<< orphan*/ * aclcopy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * acldefault (int,int /*<<< orphan*/ ) ; 
 scalar_t__ aclequal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aclitemsort (int /*<<< orphan*/ *) ; 
 int aclmembers (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 TYPE_3__* heap_form_tuple (int /*<<< orphan*/ ,int*,int*) ; 
 TYPE_3__* heap_modify_tuple (TYPE_3__*,int /*<<< orphan*/ ,int*,int*,int*) ; 
 int /*<<< orphan*/ * make_empty_acl () ; 
 int /*<<< orphan*/ * merge_acl_with_grant (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  performDeletion (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recordDependencyOn (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recordDependencyOnOwner (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  updateAclDependencies (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
SetDefaultACL(InternalDefaultACL *iacls)
{
	AclMode		this_privileges = iacls->privileges;
	char		objtype;
	Relation	rel;
	HeapTuple	tuple;
	bool		isNew;
	Acl		   *def_acl;
	Acl		   *old_acl;
	Acl		   *new_acl;
	HeapTuple	newtuple;
	Datum		values[Natts_pg_default_acl];
	bool		nulls[Natts_pg_default_acl];
	bool		replaces[Natts_pg_default_acl];
	int			noldmembers;
	int			nnewmembers;
	Oid		   *oldmembers;
	Oid		   *newmembers;

	rel = table_open(DefaultAclRelationId, RowExclusiveLock);

	/*
	 * The default for a global entry is the hard-wired default ACL for the
	 * particular object type.  The default for non-global entries is an empty
	 * ACL.  This must be so because global entries replace the hard-wired
	 * defaults, while others are added on.
	 */
	if (!OidIsValid(iacls->nspid))
		def_acl = acldefault(iacls->objtype, iacls->roleid);
	else
		def_acl = make_empty_acl();

	/*
	 * Convert ACL object type to pg_default_acl object type and handle
	 * all_privs option
	 */
	switch (iacls->objtype)
	{
		case OBJECT_TABLE:
			objtype = DEFACLOBJ_RELATION;
			if (iacls->all_privs && this_privileges == ACL_NO_RIGHTS)
				this_privileges = ACL_ALL_RIGHTS_RELATION;
			break;

		case OBJECT_SEQUENCE:
			objtype = DEFACLOBJ_SEQUENCE;
			if (iacls->all_privs && this_privileges == ACL_NO_RIGHTS)
				this_privileges = ACL_ALL_RIGHTS_SEQUENCE;
			break;

		case OBJECT_FUNCTION:
			objtype = DEFACLOBJ_FUNCTION;
			if (iacls->all_privs && this_privileges == ACL_NO_RIGHTS)
				this_privileges = ACL_ALL_RIGHTS_FUNCTION;
			break;

		case OBJECT_TYPE:
			objtype = DEFACLOBJ_TYPE;
			if (iacls->all_privs && this_privileges == ACL_NO_RIGHTS)
				this_privileges = ACL_ALL_RIGHTS_TYPE;
			break;

		case OBJECT_SCHEMA:
			if (OidIsValid(iacls->nspid))
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_GRANT_OPERATION),
						 errmsg("cannot use IN SCHEMA clause when using GRANT/REVOKE ON SCHEMAS")));
			objtype = DEFACLOBJ_NAMESPACE;
			if (iacls->all_privs && this_privileges == ACL_NO_RIGHTS)
				this_privileges = ACL_ALL_RIGHTS_SCHEMA;
			break;

		default:
			elog(ERROR, "unrecognized objtype: %d",
				 (int) iacls->objtype);
			objtype = 0;		/* keep compiler quiet */
			break;
	}

	/* Search for existing row for this object type in catalog */
	tuple = SearchSysCache3(DEFACLROLENSPOBJ,
							ObjectIdGetDatum(iacls->roleid),
							ObjectIdGetDatum(iacls->nspid),
							CharGetDatum(objtype));

	if (HeapTupleIsValid(tuple))
	{
		Datum		aclDatum;
		bool		isNull;

		aclDatum = SysCacheGetAttr(DEFACLROLENSPOBJ, tuple,
								   Anum_pg_default_acl_defaclacl,
								   &isNull);
		if (!isNull)
			old_acl = DatumGetAclPCopy(aclDatum);
		else
			old_acl = NULL;		/* this case shouldn't happen, probably */
		isNew = false;
	}
	else
	{
		old_acl = NULL;
		isNew = true;
	}

	if (old_acl != NULL)
	{
		/*
		 * We need the members of both old and new ACLs so we can correct the
		 * shared dependency information.  Collect data before
		 * merge_acl_with_grant throws away old_acl.
		 */
		noldmembers = aclmembers(old_acl, &oldmembers);
	}
	else
	{
		/* If no or null entry, start with the default ACL value */
		old_acl = aclcopy(def_acl);
		/* There are no old member roles according to the catalogs */
		noldmembers = 0;
		oldmembers = NULL;
	}

	/*
	 * Generate new ACL.  Grantor of rights is always the same as the target
	 * role.
	 */
	new_acl = merge_acl_with_grant(old_acl,
								   iacls->is_grant,
								   iacls->grant_option,
								   iacls->behavior,
								   iacls->grantees,
								   this_privileges,
								   iacls->roleid,
								   iacls->roleid);

	/*
	 * If the result is the same as the default value, we do not need an
	 * explicit pg_default_acl entry, and should in fact remove the entry if
	 * it exists.  Must sort both arrays to compare properly.
	 */
	aclitemsort(new_acl);
	aclitemsort(def_acl);
	if (aclequal(new_acl, def_acl))
	{
		/* delete old entry, if indeed there is one */
		if (!isNew)
		{
			ObjectAddress myself;

			/*
			 * The dependency machinery will take care of removing all
			 * associated dependency entries.  We use DROP_RESTRICT since
			 * there shouldn't be anything depending on this entry.
			 */
			myself.classId = DefaultAclRelationId;
			myself.objectId = ((Form_pg_default_acl) GETSTRUCT(tuple))->oid;
			myself.objectSubId = 0;

			performDeletion(&myself, DROP_RESTRICT, 0);
		}
	}
	else
	{
		Oid			defAclOid;

		/* Prepare to insert or update pg_default_acl entry */
		MemSet(values, 0, sizeof(values));
		MemSet(nulls, false, sizeof(nulls));
		MemSet(replaces, false, sizeof(replaces));

		if (isNew)
		{
			/* insert new entry */
			defAclOid = GetNewOidWithIndex(rel, DefaultAclOidIndexId,
										   Anum_pg_default_acl_oid);
			values[Anum_pg_default_acl_oid - 1] = ObjectIdGetDatum(defAclOid);
			values[Anum_pg_default_acl_defaclrole - 1] = ObjectIdGetDatum(iacls->roleid);
			values[Anum_pg_default_acl_defaclnamespace - 1] = ObjectIdGetDatum(iacls->nspid);
			values[Anum_pg_default_acl_defaclobjtype - 1] = CharGetDatum(objtype);
			values[Anum_pg_default_acl_defaclacl - 1] = PointerGetDatum(new_acl);

			newtuple = heap_form_tuple(RelationGetDescr(rel), values, nulls);
			CatalogTupleInsert(rel, newtuple);
		}
		else
		{
			defAclOid = ((Form_pg_default_acl) GETSTRUCT(tuple))->oid;

			/* update existing entry */
			values[Anum_pg_default_acl_defaclacl - 1] = PointerGetDatum(new_acl);
			replaces[Anum_pg_default_acl_defaclacl - 1] = true;

			newtuple = heap_modify_tuple(tuple, RelationGetDescr(rel),
										 values, nulls, replaces);
			CatalogTupleUpdate(rel, &newtuple->t_self, newtuple);
		}

		/* these dependencies don't change in an update */
		if (isNew)
		{
			/* dependency on role */
			recordDependencyOnOwner(DefaultAclRelationId, defAclOid,
									iacls->roleid);

			/* dependency on namespace */
			if (OidIsValid(iacls->nspid))
			{
				ObjectAddress myself,
							referenced;

				myself.classId = DefaultAclRelationId;
				myself.objectId = defAclOid;
				myself.objectSubId = 0;

				referenced.classId = NamespaceRelationId;
				referenced.objectId = iacls->nspid;
				referenced.objectSubId = 0;

				recordDependencyOn(&myself, &referenced, DEPENDENCY_AUTO);
			}
		}

		/*
		 * Update the shared dependency ACL info
		 */
		nnewmembers = aclmembers(new_acl, &newmembers);

		updateAclDependencies(DefaultAclRelationId,
							  defAclOid, 0,
							  iacls->roleid,
							  noldmembers, oldmembers,
							  nnewmembers, newmembers);

		if (isNew)
			InvokeObjectPostCreateHook(DefaultAclRelationId, defAclOid, 0);
		else
			InvokeObjectPostAlterHook(DefaultAclRelationId, defAclOid, 0);
	}

	if (HeapTupleIsValid(tuple))
		ReleaseSysCache(tuple);

	table_close(rel, RowExclusiveLock);
}