#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Value ;
typedef  TYPE_1__* TupleDesc ;
struct TYPE_11__ {void* colnames; int /*<<< orphan*/  aliasname; } ;
struct TYPE_10__ {int /*<<< orphan*/  attname; scalar_t__ attisdropped; } ;
struct TYPE_9__ {int natts; } ;
typedef  int /*<<< orphan*/  ListCell ;
typedef  void List ;
typedef  TYPE_2__* Form_pg_attribute ;
typedef  TYPE_3__ Alias ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_INVALID_COLUMN_REFERENCE ; 
 int /*<<< orphan*/  ERROR ; 
 void* NIL ; 
 char* NameStr (int /*<<< orphan*/ ) ; 
 TYPE_2__* TupleDescAttr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int,int) ; 
 void* lappend (void*,int /*<<< orphan*/ *) ; 
 scalar_t__ lfirst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_head (void*) ; 
 int list_length (void*) ; 
 int /*<<< orphan*/ * lnext (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * makeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pstrdup (char*) ; 

__attribute__((used)) static void
buildRelationAliases(TupleDesc tupdesc, Alias *alias, Alias *eref)
{
	int			maxattrs = tupdesc->natts;
	List	   *aliaslist;
	ListCell   *aliaslc;
	int			numaliases;
	int			varattno;
	int			numdropped = 0;

	Assert(eref->colnames == NIL);

	if (alias)
	{
		aliaslist = alias->colnames;
		aliaslc = list_head(aliaslist);
		numaliases = list_length(aliaslist);
		/* We'll rebuild the alias colname list */
		alias->colnames = NIL;
	}
	else
	{
		aliaslist = NIL;
		aliaslc = NULL;
		numaliases = 0;
	}

	for (varattno = 0; varattno < maxattrs; varattno++)
	{
		Form_pg_attribute attr = TupleDescAttr(tupdesc, varattno);
		Value	   *attrname;

		if (attr->attisdropped)
		{
			/* Always insert an empty string for a dropped column */
			attrname = makeString(pstrdup(""));
			if (aliaslc)
				alias->colnames = lappend(alias->colnames, attrname);
			numdropped++;
		}
		else if (aliaslc)
		{
			/* Use the next user-supplied alias */
			attrname = (Value *) lfirst(aliaslc);
			aliaslc = lnext(aliaslist, aliaslc);
			alias->colnames = lappend(alias->colnames, attrname);
		}
		else
		{
			attrname = makeString(pstrdup(NameStr(attr->attname)));
			/* we're done with the alias if any */
		}

		eref->colnames = lappend(eref->colnames, attrname);
	}

	/* Too many user-supplied aliases? */
	if (aliaslc)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_COLUMN_REFERENCE),
				 errmsg("table \"%s\" has %d columns available but %d columns specified",
						eref->aliasname, maxattrs - numdropped, numaliases)));
}