#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* rd_rel; } ;
struct TYPE_5__ {scalar_t__ relkind; } ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  PartitionKey ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  ListCell ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Bitmapset ;
typedef  scalar_t__ AttrNumber ;

/* Variables and functions */
 scalar_t__ FirstLowInvalidHeapAttributeNumber ; 
 scalar_t__ RELKIND_PARTITIONED_TABLE ; 
 int /*<<< orphan*/  RelationGetPartitionKey (TYPE_2__*) ; 
 scalar_t__ bms_is_member (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ bms_overlap (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ get_partition_col_attnum (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * get_partition_exprs (int /*<<< orphan*/ ) ; 
 int get_partition_natts (int /*<<< orphan*/ ) ; 
 scalar_t__ lfirst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lnext (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pull_varattnos (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 

bool
has_partition_attrs(Relation rel, Bitmapset *attnums, bool *used_in_expr)
{
	PartitionKey key;
	int			partnatts;
	List	   *partexprs;
	ListCell   *partexprs_item;
	int			i;

	if (attnums == NULL || rel->rd_rel->relkind != RELKIND_PARTITIONED_TABLE)
		return false;

	key = RelationGetPartitionKey(rel);
	partnatts = get_partition_natts(key);
	partexprs = get_partition_exprs(key);

	partexprs_item = list_head(partexprs);
	for (i = 0; i < partnatts; i++)
	{
		AttrNumber	partattno = get_partition_col_attnum(key, i);

		if (partattno != 0)
		{
			if (bms_is_member(partattno - FirstLowInvalidHeapAttributeNumber,
							  attnums))
			{
				if (used_in_expr)
					*used_in_expr = false;
				return true;
			}
		}
		else
		{
			/* Arbitrary expression */
			Node	   *expr = (Node *) lfirst(partexprs_item);
			Bitmapset  *expr_attrs = NULL;

			/* Find all attributes referenced */
			pull_varattnos(expr, 1, &expr_attrs);
			partexprs_item = lnext(partexprs, partexprs_item);

			if (bms_overlap(attnums, expr_attrs))
			{
				if (used_in_expr)
					*used_in_expr = true;
				return true;
			}
		}
	}

	return false;
}