#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Var ;
typedef  int /*<<< orphan*/  TargetEntry ;
struct TYPE_9__ {int atttypmod; int /*<<< orphan*/  attname; int /*<<< orphan*/  attcollation; int /*<<< orphan*/  atttypid; scalar_t__ attisdropped; } ;
struct TYPE_8__ {TYPE_1__* rd_rel; int /*<<< orphan*/  rd_att; } ;
struct TYPE_7__ {int /*<<< orphan*/  reltype; } ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Index ;
typedef  TYPE_3__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  INT4OID ; 
 int InvalidAttrNumber ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int RelationGetNumberOfAttributes (TYPE_2__*) ; 
 TYPE_3__* TupleDescAttr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ makeNullConst (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * makeTargetEntry (int /*<<< orphan*/ *,int,char*,int) ; 
 int /*<<< orphan*/ * makeVar (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* pstrdup (int /*<<< orphan*/ ) ; 

List *
BuildOnConflictExcludedTargetlist(Relation targetrel,
								  Index exclRelIndex)
{
	List	   *result = NIL;
	int			attno;
	Var		   *var;
	TargetEntry *te;

	/*
	 * Note that resnos of the tlist must correspond to attnos of the
	 * underlying relation, hence we need entries for dropped columns too.
	 */
	for (attno = 0; attno < RelationGetNumberOfAttributes(targetrel); attno++)
	{
		Form_pg_attribute attr = TupleDescAttr(targetrel->rd_att, attno);
		char	   *name;

		if (attr->attisdropped)
		{
			/*
			 * can't use atttypid here, but it doesn't really matter what type
			 * the Const claims to be.
			 */
			var = (Var *) makeNullConst(INT4OID, -1, InvalidOid);
			name = NULL;
		}
		else
		{
			var = makeVar(exclRelIndex, attno + 1,
						  attr->atttypid, attr->atttypmod,
						  attr->attcollation,
						  0);
			name = pstrdup(NameStr(attr->attname));
		}

		te = makeTargetEntry((Expr *) var,
							 attno + 1,
							 name,
							 false);

		result = lappend(result, te);
	}

	/*
	 * Add a whole-row-Var entry to support references to "EXCLUDED.*".  Like
	 * the other entries in the EXCLUDED tlist, its resno must match the Var's
	 * varattno, else the wrong things happen while resolving references in
	 * setrefs.c.  This is against normal conventions for targetlists, but
	 * it's okay since we don't use this as a real tlist.
	 */
	var = makeVar(exclRelIndex, InvalidAttrNumber,
				  targetrel->rd_rel->reltype,
				  -1, InvalidOid, 0);
	te = makeTargetEntry((Expr *) var, InvalidAttrNumber, NULL, true);
	result = lappend(result, te);

	return result;
}