#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ xfs_dahash_t ;
struct xfs_da_state_blk {int /*<<< orphan*/  index; } ;
struct xfs_da_node_entry {int /*<<< orphan*/  hashval; } ;
struct xchk_da_btree {scalar_t__* hashes; TYPE_2__* state; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_3__ {struct xfs_da_state_blk* blk; } ;
struct TYPE_4__ {TYPE_1__ path; } ;

/* Variables and functions */
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 struct xfs_da_node_entry* xchk_da_btree_entry (struct xchk_da_btree*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xchk_da_set_corrupt (struct xchk_da_btree*,int) ; 

int
xchk_da_btree_hash(
	struct xchk_da_btree		*ds,
	int				level,
	__be32				*hashp)
{
	struct xfs_da_state_blk		*blks;
	struct xfs_da_node_entry	*entry;
	xfs_dahash_t			hash;
	xfs_dahash_t			parent_hash;

	/* Is this hash in order? */
	hash = be32_to_cpu(*hashp);
	if (hash < ds->hashes[level])
		xchk_da_set_corrupt(ds, level);
	ds->hashes[level] = hash;

	if (level == 0)
		return 0;

	/* Is this hash no larger than the parent hash? */
	blks = ds->state->path.blk;
	entry = xchk_da_btree_entry(ds, level - 1, blks[level - 1].index);
	parent_hash = be32_to_cpu(entry->hashval);
	if (parent_hash < hash)
		xchk_da_set_corrupt(ds, level);

	return 0;
}