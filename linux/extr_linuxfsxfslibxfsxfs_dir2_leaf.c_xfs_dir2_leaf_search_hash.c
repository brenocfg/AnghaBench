#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_dir2_leaf_t ;
struct xfs_dir2_leaf_entry {int /*<<< orphan*/  hashval; } ;
typedef  struct xfs_dir2_leaf_entry xfs_dir2_leaf_entry_t ;
typedef  scalar_t__ xfs_dahash_t ;
struct TYPE_7__ {scalar_t__ hashval; TYPE_2__* dp; } ;
typedef  TYPE_3__ xfs_da_args_t ;
struct xfs_dir3_icleaf_hdr {int count; } ;
struct xfs_buf {int /*<<< orphan*/ * b_addr; } ;
struct TYPE_6__ {TYPE_1__* d_ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* leaf_hdr_from_disk ) (struct xfs_dir3_icleaf_hdr*,int /*<<< orphan*/ *) ;struct xfs_dir2_leaf_entry* (* leaf_ents_p ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 struct xfs_dir2_leaf_entry* stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct xfs_dir3_icleaf_hdr*,int /*<<< orphan*/ *) ; 

int						/* index value */
xfs_dir2_leaf_search_hash(
	xfs_da_args_t		*args,		/* operation arguments */
	struct xfs_buf		*lbp)		/* leaf buffer */
{
	xfs_dahash_t		hash=0;		/* hash from this entry */
	xfs_dahash_t		hashwant;	/* hash value looking for */
	int			high;		/* high leaf index */
	int			low;		/* low leaf index */
	xfs_dir2_leaf_t		*leaf;		/* leaf structure */
	xfs_dir2_leaf_entry_t	*lep;		/* leaf entry */
	int			mid=0;		/* current leaf index */
	struct xfs_dir2_leaf_entry *ents;
	struct xfs_dir3_icleaf_hdr leafhdr;

	leaf = lbp->b_addr;
	ents = args->dp->d_ops->leaf_ents_p(leaf);
	args->dp->d_ops->leaf_hdr_from_disk(&leafhdr, leaf);

	/*
	 * Note, the table cannot be empty, so we have to go through the loop.
	 * Binary search the leaf entries looking for our hash value.
	 */
	for (lep = ents, low = 0, high = leafhdr.count - 1,
		hashwant = args->hashval;
	     low <= high; ) {
		mid = (low + high) >> 1;
		if ((hash = be32_to_cpu(lep[mid].hashval)) == hashwant)
			break;
		if (hash < hashwant)
			low = mid + 1;
		else
			high = mid - 1;
	}
	/*
	 * Found one, back up through all the equal hash values.
	 */
	if (hash == hashwant) {
		while (mid > 0 && be32_to_cpu(lep[mid - 1].hashval) == hashwant) {
			mid--;
		}
	}
	/*
	 * Need to point to an entry higher than ours.
	 */
	else if (hash < hashwant)
		mid++;
	return mid;
}