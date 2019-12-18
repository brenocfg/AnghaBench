#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_18__ {int relnatts; } ;
struct TYPE_17__ {int atttypid; int atttypmod; int /*<<< orphan*/  attalign; int /*<<< orphan*/  attstorage; int /*<<< orphan*/  attbyval; int /*<<< orphan*/  attndims; int /*<<< orphan*/  attlen; int /*<<< orphan*/  attname; } ;
struct TYPE_16__ {int attnum; int attstattarget; int attcacheoff; int attislocal; int attcollation; int atttypid; int atttypmod; int attrelid; int /*<<< orphan*/  attstorage; int /*<<< orphan*/  attalign; int /*<<< orphan*/  attbyval; int /*<<< orphan*/  attlen; int /*<<< orphan*/  attname; int /*<<< orphan*/  attndims; } ;
struct TYPE_15__ {int opckeytype; scalar_t__ opcintype; } ;
struct TYPE_14__ {int /*<<< orphan*/  typstorage; int /*<<< orphan*/  typalign; int /*<<< orphan*/  typbyval; int /*<<< orphan*/  typlen; } ;
struct TYPE_13__ {int amkeytype; } ;
struct TYPE_12__ {int ii_NumIndexAttrs; int ii_NumIndexKeyAttrs; int* ii_IndexAttrNumbers; int /*<<< orphan*/ * ii_Expressions; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  ListCell ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__ IndexInfo ;
typedef  TYPE_2__ IndexAmRoutine ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_3__* Form_pg_type ;
typedef  TYPE_4__* Form_pg_opclass ;
typedef  TYPE_5__* Form_pg_attribute ;
typedef  TYPE_6__ FormData_pg_attribute ;
typedef  int AttrNumber ;

/* Variables and functions */
 scalar_t__ ANYARRAYOID ; 
 int ANYELEMENTOID ; 
 int /*<<< orphan*/  ATTRIBUTE_FIXED_PART_SIZE ; 
 int /*<<< orphan*/  Assert (int) ; 
 int AttrNumberGetAttrOffset (int) ; 
 int /*<<< orphan*/  CLAOID ; 
 int /*<<< orphan*/  CheckAttributeType (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateTemplateTupleDesc (int) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 TYPE_2__* GetIndexAmRoutineByAmId (int,int) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int InvalidOid ; 
 int /*<<< orphan*/  MemSet (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int) ; 
 scalar_t__ OidIsValid (int) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 TYPE_8__* RelationGetForm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPEOID ; 
 void* TupleDescAttr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int exprType (int /*<<< orphan*/ *) ; 
 int exprTypmod (int /*<<< orphan*/ *) ; 
 int get_base_element_type (int) ; 
 scalar_t__ lfirst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lnext (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  namecpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  namestrcpy (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  pfree (TYPE_2__*) ; 

__attribute__((used)) static TupleDesc
ConstructTupleDescriptor(Relation heapRelation,
						 IndexInfo *indexInfo,
						 List *indexColNames,
						 Oid accessMethodObjectId,
						 Oid *collationObjectId,
						 Oid *classObjectId)
{
	int			numatts = indexInfo->ii_NumIndexAttrs;
	int			numkeyatts = indexInfo->ii_NumIndexKeyAttrs;
	ListCell   *colnames_item = list_head(indexColNames);
	ListCell   *indexpr_item = list_head(indexInfo->ii_Expressions);
	IndexAmRoutine *amroutine;
	TupleDesc	heapTupDesc;
	TupleDesc	indexTupDesc;
	int			natts;			/* #atts in heap rel --- for error checks */
	int			i;

	/* We need access to the index AM's API struct */
	amroutine = GetIndexAmRoutineByAmId(accessMethodObjectId, false);

	/* ... and to the table's tuple descriptor */
	heapTupDesc = RelationGetDescr(heapRelation);
	natts = RelationGetForm(heapRelation)->relnatts;

	/*
	 * allocate the new tuple descriptor
	 */
	indexTupDesc = CreateTemplateTupleDesc(numatts);

	/*
	 * Fill in the pg_attribute row.
	 */
	for (i = 0; i < numatts; i++)
	{
		AttrNumber	atnum = indexInfo->ii_IndexAttrNumbers[i];
		Form_pg_attribute to = TupleDescAttr(indexTupDesc, i);
		HeapTuple	tuple;
		Form_pg_type typeTup;
		Form_pg_opclass opclassTup;
		Oid			keyType;

		MemSet(to, 0, ATTRIBUTE_FIXED_PART_SIZE);
		to->attnum = i + 1;
		to->attstattarget = -1;
		to->attcacheoff = -1;
		to->attislocal = true;
		to->attcollation = (i < numkeyatts) ?
			collationObjectId[i] : InvalidOid;

		/*
		 * For simple index columns, we copy some pg_attribute fields from the
		 * parent relation.  For expressions we have to look at the expression
		 * result.
		 */
		if (atnum != 0)
		{
			/* Simple index column */
			const FormData_pg_attribute *from;

			Assert(atnum > 0);	/* should've been caught above */

			if (atnum > natts)	/* safety check */
				elog(ERROR, "invalid column number %d", atnum);
			from = TupleDescAttr(heapTupDesc,
								 AttrNumberGetAttrOffset(atnum));

			namecpy(&to->attname, &from->attname);
			to->atttypid = from->atttypid;
			to->attlen = from->attlen;
			to->attndims = from->attndims;
			to->atttypmod = from->atttypmod;
			to->attbyval = from->attbyval;
			to->attstorage = from->attstorage;
			to->attalign = from->attalign;
		}
		else
		{
			/* Expressional index */
			Node	   *indexkey;

			if (indexpr_item == NULL)	/* shouldn't happen */
				elog(ERROR, "too few entries in indexprs list");
			indexkey = (Node *) lfirst(indexpr_item);
			indexpr_item = lnext(indexInfo->ii_Expressions, indexpr_item);

			/*
			 * Lookup the expression type in pg_type for the type length etc.
			 */
			keyType = exprType(indexkey);
			tuple = SearchSysCache1(TYPEOID, ObjectIdGetDatum(keyType));
			if (!HeapTupleIsValid(tuple))
				elog(ERROR, "cache lookup failed for type %u", keyType);
			typeTup = (Form_pg_type) GETSTRUCT(tuple);

			/*
			 * Assign some of the attributes values. Leave the rest.
			 */
			to->atttypid = keyType;
			to->attlen = typeTup->typlen;
			to->attbyval = typeTup->typbyval;
			to->attstorage = typeTup->typstorage;
			to->attalign = typeTup->typalign;
			to->atttypmod = exprTypmod(indexkey);

			ReleaseSysCache(tuple);

			/*
			 * Make sure the expression yields a type that's safe to store in
			 * an index.  We need this defense because we have index opclasses
			 * for pseudo-types such as "record", and the actually stored type
			 * had better be safe; eg, a named composite type is okay, an
			 * anonymous record type is not.  The test is the same as for
			 * whether a table column is of a safe type (which is why we
			 * needn't check for the non-expression case).
			 */
			CheckAttributeType(NameStr(to->attname),
							   to->atttypid, to->attcollation,
							   NIL, 0);
		}

		/*
		 * We do not yet have the correct relation OID for the index, so just
		 * set it invalid for now.  InitializeAttributeOids() will fix it
		 * later.
		 */
		to->attrelid = InvalidOid;

		/*
		 * Set the attribute name as specified by caller.
		 */
		if (colnames_item == NULL)	/* shouldn't happen */
			elog(ERROR, "too few entries in colnames list");
		namestrcpy(&to->attname, (const char *) lfirst(colnames_item));
		colnames_item = lnext(indexColNames, colnames_item);

		/*
		 * Check the opclass and index AM to see if either provides a keytype
		 * (overriding the attribute type).  Opclass (if exists) takes
		 * precedence.
		 */
		keyType = amroutine->amkeytype;

		/*
		 * Code below is concerned to the opclasses which are not used with
		 * the included columns.
		 */
		if (i < indexInfo->ii_NumIndexKeyAttrs)
		{
			tuple = SearchSysCache1(CLAOID, ObjectIdGetDatum(classObjectId[i]));
			if (!HeapTupleIsValid(tuple))
				elog(ERROR, "cache lookup failed for opclass %u",
					 classObjectId[i]);
			opclassTup = (Form_pg_opclass) GETSTRUCT(tuple);
			if (OidIsValid(opclassTup->opckeytype))
				keyType = opclassTup->opckeytype;

			/*
			 * If keytype is specified as ANYELEMENT, and opcintype is
			 * ANYARRAY, then the attribute type must be an array (else it'd
			 * not have matched this opclass); use its element type.
			 */
			if (keyType == ANYELEMENTOID && opclassTup->opcintype == ANYARRAYOID)
			{
				keyType = get_base_element_type(to->atttypid);
				if (!OidIsValid(keyType))
					elog(ERROR, "could not get element type of array type %u",
						 to->atttypid);
			}

			ReleaseSysCache(tuple);
		}

		/*
		 * If a key type different from the heap value is specified, update
		 * the type-related fields in the index tupdesc.
		 */
		if (OidIsValid(keyType) && keyType != to->atttypid)
		{
			tuple = SearchSysCache1(TYPEOID, ObjectIdGetDatum(keyType));
			if (!HeapTupleIsValid(tuple))
				elog(ERROR, "cache lookup failed for type %u", keyType);
			typeTup = (Form_pg_type) GETSTRUCT(tuple);

			to->atttypid = keyType;
			to->atttypmod = -1;
			to->attlen = typeTup->typlen;
			to->attbyval = typeTup->typbyval;
			to->attalign = typeTup->typalign;
			to->attstorage = typeTup->typstorage;

			ReleaseSysCache(tuple);
		}
	}

	pfree(amroutine);

	return indexTupDesc;
}