#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  nparts; int /*<<< orphan*/  boundinfo; } ;
struct TYPE_13__ {TYPE_1__* glob; } ;
struct TYPE_12__ {int /*<<< orphan*/  nparts; int /*<<< orphan*/  boundinfo; int /*<<< orphan*/ * part_scheme; } ;
struct TYPE_11__ {int /*<<< orphan*/ * partition_directory; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_2__ RelOptInfo ;
typedef  TYPE_3__ PlannerInfo ;
typedef  TYPE_4__* PartitionDesc ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ * CreatePartitionDirectory (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 TYPE_4__* PartitionDirectoryLookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * find_partition_scheme (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_baserel_partition_constraint (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  set_baserel_partition_key_exprs (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void
set_relation_partition_info(PlannerInfo *root, RelOptInfo *rel,
							Relation relation)
{
	PartitionDesc partdesc;

	/* Create the PartitionDirectory infrastructure if we didn't already */
	if (root->glob->partition_directory == NULL)
		root->glob->partition_directory =
			CreatePartitionDirectory(CurrentMemoryContext);

	partdesc = PartitionDirectoryLookup(root->glob->partition_directory,
										relation);
	rel->part_scheme = find_partition_scheme(root, relation);
	Assert(partdesc != NULL && rel->part_scheme != NULL);
	rel->boundinfo = partdesc->boundinfo;
	rel->nparts = partdesc->nparts;
	set_baserel_partition_key_exprs(relation, rel);
	set_baserel_partition_constraint(relation, rel);
}