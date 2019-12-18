#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__* values; } ;
typedef  TYPE_2__ oidvector ;
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_17__ {int* values; } ;
typedef  TYPE_3__ int2vector ;
typedef  int int16 ;
struct TYPE_22__ {int /*<<< orphan*/  amname; int /*<<< orphan*/  amhandler; } ;
struct TYPE_21__ {scalar_t__ relam; scalar_t__ relkind; int /*<<< orphan*/  relname; } ;
struct TYPE_15__ {scalar_t__* values; } ;
struct TYPE_20__ {scalar_t__ indrelid; scalar_t__ indexrelid; int indnatts; int indnkeyatts; TYPE_1__ indkey; scalar_t__ indisunique; } ;
struct TYPE_19__ {scalar_t__ amcanorder; } ;
struct TYPE_18__ {char* data; } ;
typedef  TYPE_4__ StringInfoData ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  ListCell ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_5__ IndexAmRoutine ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_6__* Form_pg_index ;
typedef  TYPE_7__* Form_pg_class ;
typedef  TYPE_8__* Form_pg_am ;
typedef  int /*<<< orphan*/  Datum ;
typedef  scalar_t__ AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  AMOID ; 
 int /*<<< orphan*/  Anum_pg_index_indclass ; 
 int /*<<< orphan*/  Anum_pg_index_indcollation ; 
 int /*<<< orphan*/  Anum_pg_index_indexprs ; 
 int /*<<< orphan*/  Anum_pg_index_indoption ; 
 int /*<<< orphan*/  Anum_pg_index_indpred ; 
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 TYPE_5__* GetIndexAmRoutine (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INDEXRELID ; 
 int INDOPTION_DESC ; 
 int INDOPTION_NULLS_FIRST ; 
 int /*<<< orphan*/ * NIL ; 
 char* NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 scalar_t__ OidIsValid (scalar_t__) ; 
 int PRETTYFLAG_SCHEMA ; 
 scalar_t__ RELKIND_PARTITIONED_INDEX ; 
 int /*<<< orphan*/  RELOID ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysCacheGetAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 char* TextDatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_4__*,char*,char*,...) ; 
 int /*<<< orphan*/  appendStringInfoChar (TYPE_4__*,char) ; 
 int /*<<< orphan*/  appendStringInfoString (TYPE_4__*,char*) ; 
 int /*<<< orphan*/ * deparse_context_for (int /*<<< orphan*/ ,scalar_t__) ; 
 char* deparse_expression_pretty (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ exprCollation (int /*<<< orphan*/ *) ; 
 scalar_t__ exprType (int /*<<< orphan*/ *) ; 
 char* flatten_reloptions (scalar_t__) ; 
 char* generate_collation_name (scalar_t__) ; 
 char* generate_operator_name (scalar_t__ const,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  generate_qualified_relation_name (scalar_t__) ; 
 int /*<<< orphan*/  generate_relation_name (scalar_t__,int /*<<< orphan*/ *) ; 
 char* get_attname (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  get_atttypetypmodcoll (scalar_t__,scalar_t__,scalar_t__*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  get_opclass_name (scalar_t__,scalar_t__,TYPE_4__*) ; 
 scalar_t__ get_rel_tablespace (scalar_t__) ; 
 int /*<<< orphan*/  get_relation_name (scalar_t__) ; 
 char* get_tablespace_name (scalar_t__) ; 
 int /*<<< orphan*/  heap_attisnull (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_4__*) ; 
 scalar_t__ lfirst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lnext (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ looks_like_function (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 char* quote_identifier (char*) ; 
 scalar_t__ stringToNode (char*) ; 

__attribute__((used)) static char *
pg_get_indexdef_worker(Oid indexrelid, int colno,
					   const Oid *excludeOps,
					   bool attrsOnly, bool keysOnly,
					   bool showTblSpc, bool inherits,
					   int prettyFlags, bool missing_ok)
{
	/* might want a separate isConstraint parameter later */
	bool		isConstraint = (excludeOps != NULL);
	HeapTuple	ht_idx;
	HeapTuple	ht_idxrel;
	HeapTuple	ht_am;
	Form_pg_index idxrec;
	Form_pg_class idxrelrec;
	Form_pg_am	amrec;
	IndexAmRoutine *amroutine;
	List	   *indexprs;
	ListCell   *indexpr_item;
	List	   *context;
	Oid			indrelid;
	int			keyno;
	Datum		indcollDatum;
	Datum		indclassDatum;
	Datum		indoptionDatum;
	bool		isnull;
	oidvector  *indcollation;
	oidvector  *indclass;
	int2vector *indoption;
	StringInfoData buf;
	char	   *str;
	char	   *sep;

	/*
	 * Fetch the pg_index tuple by the Oid of the index
	 */
	ht_idx = SearchSysCache1(INDEXRELID, ObjectIdGetDatum(indexrelid));
	if (!HeapTupleIsValid(ht_idx))
	{
		if (missing_ok)
			return NULL;
		elog(ERROR, "cache lookup failed for index %u", indexrelid);
	}
	idxrec = (Form_pg_index) GETSTRUCT(ht_idx);

	indrelid = idxrec->indrelid;
	Assert(indexrelid == idxrec->indexrelid);

	/* Must get indcollation, indclass, and indoption the hard way */
	indcollDatum = SysCacheGetAttr(INDEXRELID, ht_idx,
								   Anum_pg_index_indcollation, &isnull);
	Assert(!isnull);
	indcollation = (oidvector *) DatumGetPointer(indcollDatum);

	indclassDatum = SysCacheGetAttr(INDEXRELID, ht_idx,
									Anum_pg_index_indclass, &isnull);
	Assert(!isnull);
	indclass = (oidvector *) DatumGetPointer(indclassDatum);

	indoptionDatum = SysCacheGetAttr(INDEXRELID, ht_idx,
									 Anum_pg_index_indoption, &isnull);
	Assert(!isnull);
	indoption = (int2vector *) DatumGetPointer(indoptionDatum);

	/*
	 * Fetch the pg_class tuple of the index relation
	 */
	ht_idxrel = SearchSysCache1(RELOID, ObjectIdGetDatum(indexrelid));
	if (!HeapTupleIsValid(ht_idxrel))
		elog(ERROR, "cache lookup failed for relation %u", indexrelid);
	idxrelrec = (Form_pg_class) GETSTRUCT(ht_idxrel);

	/*
	 * Fetch the pg_am tuple of the index' access method
	 */
	ht_am = SearchSysCache1(AMOID, ObjectIdGetDatum(idxrelrec->relam));
	if (!HeapTupleIsValid(ht_am))
		elog(ERROR, "cache lookup failed for access method %u",
			 idxrelrec->relam);
	amrec = (Form_pg_am) GETSTRUCT(ht_am);

	/* Fetch the index AM's API struct */
	amroutine = GetIndexAmRoutine(amrec->amhandler);

	/*
	 * Get the index expressions, if any.  (NOTE: we do not use the relcache
	 * versions of the expressions and predicate, because we want to display
	 * non-const-folded expressions.)
	 */
	if (!heap_attisnull(ht_idx, Anum_pg_index_indexprs, NULL))
	{
		Datum		exprsDatum;
		bool		isnull;
		char	   *exprsString;

		exprsDatum = SysCacheGetAttr(INDEXRELID, ht_idx,
									 Anum_pg_index_indexprs, &isnull);
		Assert(!isnull);
		exprsString = TextDatumGetCString(exprsDatum);
		indexprs = (List *) stringToNode(exprsString);
		pfree(exprsString);
	}
	else
		indexprs = NIL;

	indexpr_item = list_head(indexprs);

	context = deparse_context_for(get_relation_name(indrelid), indrelid);

	/*
	 * Start the index definition.  Note that the index's name should never be
	 * schema-qualified, but the indexed rel's name may be.
	 */
	initStringInfo(&buf);

	if (!attrsOnly)
	{
		if (!isConstraint)
			appendStringInfo(&buf, "CREATE %sINDEX %s ON %s%s USING %s (",
							 idxrec->indisunique ? "UNIQUE " : "",
							 quote_identifier(NameStr(idxrelrec->relname)),
							 idxrelrec->relkind == RELKIND_PARTITIONED_INDEX
							 && !inherits ? "ONLY " : "",
							 (prettyFlags & PRETTYFLAG_SCHEMA) ?
							 generate_relation_name(indrelid, NIL) :
							 generate_qualified_relation_name(indrelid),
							 quote_identifier(NameStr(amrec->amname)));
		else					/* currently, must be EXCLUDE constraint */
			appendStringInfo(&buf, "EXCLUDE USING %s (",
							 quote_identifier(NameStr(amrec->amname)));
	}

	/*
	 * Report the indexed attributes
	 */
	sep = "";
	for (keyno = 0; keyno < idxrec->indnatts; keyno++)
	{
		AttrNumber	attnum = idxrec->indkey.values[keyno];
		Oid			keycoltype;
		Oid			keycolcollation;

		/*
		 * Ignore non-key attributes if told to.
		 */
		if (keysOnly && keyno >= idxrec->indnkeyatts)
			break;

		/* Otherwise, print INCLUDE to divide key and non-key attrs. */
		if (!colno && keyno == idxrec->indnkeyatts)
		{
			appendStringInfoString(&buf, ") INCLUDE (");
			sep = "";
		}

		if (!colno)
			appendStringInfoString(&buf, sep);
		sep = ", ";

		if (attnum != 0)
		{
			/* Simple index column */
			char	   *attname;
			int32		keycoltypmod;

			attname = get_attname(indrelid, attnum, false);
			if (!colno || colno == keyno + 1)
				appendStringInfoString(&buf, quote_identifier(attname));
			get_atttypetypmodcoll(indrelid, attnum,
								  &keycoltype, &keycoltypmod,
								  &keycolcollation);
		}
		else
		{
			/* expressional index */
			Node	   *indexkey;

			if (indexpr_item == NULL)
				elog(ERROR, "too few entries in indexprs list");
			indexkey = (Node *) lfirst(indexpr_item);
			indexpr_item = lnext(indexprs, indexpr_item);
			/* Deparse */
			str = deparse_expression_pretty(indexkey, context, false, false,
											prettyFlags, 0);
			if (!colno || colno == keyno + 1)
			{
				/* Need parens if it's not a bare function call */
				if (looks_like_function(indexkey))
					appendStringInfoString(&buf, str);
				else
					appendStringInfo(&buf, "(%s)", str);
			}
			keycoltype = exprType(indexkey);
			keycolcollation = exprCollation(indexkey);
		}

		/* Print additional decoration for (selected) key columns */
		if (!attrsOnly && keyno < idxrec->indnkeyatts &&
			(!colno || colno == keyno + 1))
		{
			int16		opt = indoption->values[keyno];
			Oid			indcoll = indcollation->values[keyno];

			/* Add collation, if not default for column */
			if (OidIsValid(indcoll) && indcoll != keycolcollation)
				appendStringInfo(&buf, " COLLATE %s",
								 generate_collation_name((indcoll)));

			/* Add the operator class name, if not default */
			get_opclass_name(indclass->values[keyno], keycoltype, &buf);

			/* Add options if relevant */
			if (amroutine->amcanorder)
			{
				/* if it supports sort ordering, report DESC and NULLS opts */
				if (opt & INDOPTION_DESC)
				{
					appendStringInfoString(&buf, " DESC");
					/* NULLS FIRST is the default in this case */
					if (!(opt & INDOPTION_NULLS_FIRST))
						appendStringInfoString(&buf, " NULLS LAST");
				}
				else
				{
					if (opt & INDOPTION_NULLS_FIRST)
						appendStringInfoString(&buf, " NULLS FIRST");
				}
			}

			/* Add the exclusion operator if relevant */
			if (excludeOps != NULL)
				appendStringInfo(&buf, " WITH %s",
								 generate_operator_name(excludeOps[keyno],
														keycoltype,
														keycoltype));
		}
	}

	if (!attrsOnly)
	{
		appendStringInfoChar(&buf, ')');

		/*
		 * If it has options, append "WITH (options)"
		 */
		str = flatten_reloptions(indexrelid);
		if (str)
		{
			appendStringInfo(&buf, " WITH (%s)", str);
			pfree(str);
		}

		/*
		 * Print tablespace, but only if requested
		 */
		if (showTblSpc)
		{
			Oid			tblspc;

			tblspc = get_rel_tablespace(indexrelid);
			if (OidIsValid(tblspc))
			{
				if (isConstraint)
					appendStringInfoString(&buf, " USING INDEX");
				appendStringInfo(&buf, " TABLESPACE %s",
								 quote_identifier(get_tablespace_name(tblspc)));
			}
		}

		/*
		 * If it's a partial index, decompile and append the predicate
		 */
		if (!heap_attisnull(ht_idx, Anum_pg_index_indpred, NULL))
		{
			Node	   *node;
			Datum		predDatum;
			bool		isnull;
			char	   *predString;

			/* Convert text string to node tree */
			predDatum = SysCacheGetAttr(INDEXRELID, ht_idx,
										Anum_pg_index_indpred, &isnull);
			Assert(!isnull);
			predString = TextDatumGetCString(predDatum);
			node = (Node *) stringToNode(predString);
			pfree(predString);

			/* Deparse */
			str = deparse_expression_pretty(node, context, false, false,
											prettyFlags, 0);
			if (isConstraint)
				appendStringInfo(&buf, " WHERE (%s)", str);
			else
				appendStringInfo(&buf, " WHERE %s", str);
		}
	}

	/* Clean up */
	ReleaseSysCache(ht_idx);
	ReleaseSysCache(ht_idxrel);
	ReleaseSysCache(ht_am);

	return buf.data;
}