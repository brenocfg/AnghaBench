#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  values ;
typedef  int /*<<< orphan*/  replaces ;
typedef  int /*<<< orphan*/  nulls ;
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_19__ {void* oid; } ;
struct TYPE_18__ {int /*<<< orphan*/  t_self; } ;
struct TYPE_17__ {void* objectId; scalar_t__ objectSubId; void* classId; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  void* Oid ;
typedef  TYPE_1__ ObjectAddress ;
typedef  int /*<<< orphan*/  NameData ;
typedef  TYPE_2__* HeapTuple ;
typedef  TYPE_3__* Form_pg_language ;
typedef  int Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ACLCHECK_NOT_OWNER ; 
 int Anum_pg_language_lanacl ; 
 int Anum_pg_language_laninline ; 
 int Anum_pg_language_lanispl ; 
 int Anum_pg_language_lanname ; 
 int Anum_pg_language_lanowner ; 
 int Anum_pg_language_lanplcallfoid ; 
 int Anum_pg_language_lanpltrusted ; 
 int Anum_pg_language_lanvalidator ; 
 int Anum_pg_language_oid ; 
 int BoolGetDatum (int) ; 
 int /*<<< orphan*/  CatalogTupleInsert (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  DEPENDENCY_NORMAL ; 
 int /*<<< orphan*/  ERRCODE_DUPLICATE_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GETSTRUCT (TYPE_2__*) ; 
 void* GetNewOidWithIndex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ HeapTupleIsValid (TYPE_2__*) ; 
 int /*<<< orphan*/  InvokeObjectPostCreateHook (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LANGNAME ; 
 int /*<<< orphan*/  LanguageOidIndexId ; 
 void* LanguageRelationId ; 
 int NameGetDatum (int /*<<< orphan*/ *) ; 
 int Natts_pg_language ; 
 int /*<<< orphan*/  OBJECT_LANGUAGE ; 
 int ObjectIdGetDatum (void*) ; 
 scalar_t__ OidIsValid (void*) ; 
 int /*<<< orphan*/  PointerGetDatum (char const*) ; 
 void* ProcedureRelationId ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (TYPE_2__*) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 TYPE_2__* SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aclcheck_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  deleteDependencyRecordsFor (void*,void*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 TYPE_2__* heap_form_tuple (int /*<<< orphan*/ ,int*,int*) ; 
 TYPE_2__* heap_modify_tuple (TYPE_2__*,int /*<<< orphan*/ ,int*,int*,int*) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  namestrcpy (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  pg_language_ownercheck (void*,void*) ; 
 int /*<<< orphan*/  recordDependencyOn (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recordDependencyOnCurrentExtension (TYPE_1__*,int) ; 
 int /*<<< orphan*/  recordDependencyOnOwner (void*,void*,void*) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ObjectAddress
create_proc_lang(const char *languageName, bool replace,
				 Oid languageOwner, Oid handlerOid, Oid inlineOid,
				 Oid valOid, bool trusted)
{
	Relation	rel;
	TupleDesc	tupDesc;
	Datum		values[Natts_pg_language];
	bool		nulls[Natts_pg_language];
	bool		replaces[Natts_pg_language];
	NameData	langname;
	HeapTuple	oldtup;
	HeapTuple	tup;
	Oid			langoid;
	bool		is_update;
	ObjectAddress myself,
				referenced;

	rel = table_open(LanguageRelationId, RowExclusiveLock);
	tupDesc = RelationGetDescr(rel);

	/* Prepare data to be inserted */
	memset(values, 0, sizeof(values));
	memset(nulls, false, sizeof(nulls));
	memset(replaces, true, sizeof(replaces));

	namestrcpy(&langname, languageName);
	values[Anum_pg_language_lanname - 1] = NameGetDatum(&langname);
	values[Anum_pg_language_lanowner - 1] = ObjectIdGetDatum(languageOwner);
	values[Anum_pg_language_lanispl - 1] = BoolGetDatum(true);
	values[Anum_pg_language_lanpltrusted - 1] = BoolGetDatum(trusted);
	values[Anum_pg_language_lanplcallfoid - 1] = ObjectIdGetDatum(handlerOid);
	values[Anum_pg_language_laninline - 1] = ObjectIdGetDatum(inlineOid);
	values[Anum_pg_language_lanvalidator - 1] = ObjectIdGetDatum(valOid);
	nulls[Anum_pg_language_lanacl - 1] = true;

	/* Check for pre-existing definition */
	oldtup = SearchSysCache1(LANGNAME, PointerGetDatum(languageName));

	if (HeapTupleIsValid(oldtup))
	{
		Form_pg_language oldform = (Form_pg_language) GETSTRUCT(oldtup);

		/* There is one; okay to replace it? */
		if (!replace)
			ereport(ERROR,
					(errcode(ERRCODE_DUPLICATE_OBJECT),
					 errmsg("language \"%s\" already exists", languageName)));
		if (!pg_language_ownercheck(oldform->oid, languageOwner))
			aclcheck_error(ACLCHECK_NOT_OWNER, OBJECT_LANGUAGE,
						   languageName);

		/*
		 * Do not change existing oid, ownership or permissions.  Note
		 * dependency-update code below has to agree with this decision.
		 */
		replaces[Anum_pg_language_oid - 1] = false;
		replaces[Anum_pg_language_lanowner - 1] = false;
		replaces[Anum_pg_language_lanacl - 1] = false;

		/* Okay, do it... */
		tup = heap_modify_tuple(oldtup, tupDesc, values, nulls, replaces);
		CatalogTupleUpdate(rel, &tup->t_self, tup);

		langoid = oldform->oid;
		ReleaseSysCache(oldtup);
		is_update = true;
	}
	else
	{
		/* Creating a new language */
		langoid = GetNewOidWithIndex(rel, LanguageOidIndexId,
									 Anum_pg_language_oid);
		values[Anum_pg_language_oid - 1] = ObjectIdGetDatum(langoid);
		tup = heap_form_tuple(tupDesc, values, nulls);
		CatalogTupleInsert(rel, tup);
		is_update = false;
	}

	/*
	 * Create dependencies for the new language.  If we are updating an
	 * existing language, first delete any existing pg_depend entries.
	 * (However, since we are not changing ownership or permissions, the
	 * shared dependencies do *not* need to change, and we leave them alone.)
	 */
	myself.classId = LanguageRelationId;
	myself.objectId = langoid;
	myself.objectSubId = 0;

	if (is_update)
		deleteDependencyRecordsFor(myself.classId, myself.objectId, true);

	/* dependency on owner of language */
	if (!is_update)
		recordDependencyOnOwner(myself.classId, myself.objectId,
								languageOwner);

	/* dependency on extension */
	recordDependencyOnCurrentExtension(&myself, is_update);

	/* dependency on the PL handler function */
	referenced.classId = ProcedureRelationId;
	referenced.objectId = handlerOid;
	referenced.objectSubId = 0;
	recordDependencyOn(&myself, &referenced, DEPENDENCY_NORMAL);

	/* dependency on the inline handler function, if any */
	if (OidIsValid(inlineOid))
	{
		referenced.classId = ProcedureRelationId;
		referenced.objectId = inlineOid;
		referenced.objectSubId = 0;
		recordDependencyOn(&myself, &referenced, DEPENDENCY_NORMAL);
	}

	/* dependency on the validator function, if any */
	if (OidIsValid(valOid))
	{
		referenced.classId = ProcedureRelationId;
		referenced.objectId = valOid;
		referenced.objectSubId = 0;
		recordDependencyOn(&myself, &referenced, DEPENDENCY_NORMAL);
	}

	/* Post creation hook for new procedural language */
	InvokeObjectPostCreateHook(LanguageRelationId, myself.objectId, 0);

	table_close(rel, RowExclusiveLock);

	return myself;
}