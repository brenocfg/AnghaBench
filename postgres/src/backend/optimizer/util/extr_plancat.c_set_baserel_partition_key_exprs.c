#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int partnatts; scalar_t__* partattrs; int /*<<< orphan*/  partexprs; int /*<<< orphan*/ * parttypcoll; int /*<<< orphan*/ * parttypmod; int /*<<< orphan*/ * parttypid; } ;
struct TYPE_6__ {scalar_t__ relid; int /*<<< orphan*/ ** nullable_partexprs; int /*<<< orphan*/ ** partexprs; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_1__ RelOptInfo ;
typedef  TYPE_2__* PartitionKey ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  ListCell ;
typedef  int /*<<< orphan*/  List ;
typedef  scalar_t__ Index ;
typedef  int /*<<< orphan*/  Expr ;
typedef  scalar_t__ AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ChangeVarNodes (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ IS_SIMPLE_REL (TYPE_1__*) ; 
 scalar_t__ InvalidAttrNumber ; 
 TYPE_2__* RelationGetPartitionKey (int /*<<< orphan*/ ) ; 
 scalar_t__ copyObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lfirst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_head (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_make1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lnext (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ makeVar (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int) ; 
 scalar_t__ palloc0 (int) ; 

__attribute__((used)) static void
set_baserel_partition_key_exprs(Relation relation,
								RelOptInfo *rel)
{
	PartitionKey partkey = RelationGetPartitionKey(relation);
	int			partnatts;
	int			cnt;
	List	  **partexprs;
	ListCell   *lc;
	Index		varno = rel->relid;

	Assert(IS_SIMPLE_REL(rel) && rel->relid > 0);

	/* A partitioned table should have a partition key. */
	Assert(partkey != NULL);

	partnatts = partkey->partnatts;
	partexprs = (List **) palloc(sizeof(List *) * partnatts);
	lc = list_head(partkey->partexprs);

	for (cnt = 0; cnt < partnatts; cnt++)
	{
		Expr	   *partexpr;
		AttrNumber	attno = partkey->partattrs[cnt];

		if (attno != InvalidAttrNumber)
		{
			/* Single column partition key is stored as a Var node. */
			Assert(attno > 0);

			partexpr = (Expr *) makeVar(varno, attno,
										partkey->parttypid[cnt],
										partkey->parttypmod[cnt],
										partkey->parttypcoll[cnt], 0);
		}
		else
		{
			if (lc == NULL)
				elog(ERROR, "wrong number of partition key expressions");

			/* Re-stamp the expression with given varno. */
			partexpr = (Expr *) copyObject(lfirst(lc));
			ChangeVarNodes((Node *) partexpr, 1, varno, 0);
			lc = lnext(partkey->partexprs, lc);
		}

		partexprs[cnt] = list_make1(partexpr);
	}

	rel->partexprs = partexprs;

	/*
	 * A base relation can not have nullable partition key expressions. We
	 * still allocate array of empty expressions lists to keep partition key
	 * expression handling code simple. See build_joinrel_partition_info() and
	 * match_expr_to_partition_keys().
	 */
	rel->nullable_partexprs = (List **) palloc0(sizeof(List *) * partnatts);
}