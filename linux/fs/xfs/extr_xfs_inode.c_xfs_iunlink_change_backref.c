#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ xfs_agino_t ;
struct xfs_perag {int /*<<< orphan*/  pagi_unlinked_hash; } ;
struct xfs_iunlink {scalar_t__ iu_next_unlinked; int /*<<< orphan*/  iu_rhash_head; } ;

/* Variables and functions */
 scalar_t__ NULLAGINO ; 
 int /*<<< orphan*/  kmem_free (struct xfs_iunlink*) ; 
 struct xfs_iunlink* rhashtable_lookup_fast (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ) ; 
 int rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_iunlink_hash_params ; 
 int xfs_iunlink_insert_backref (struct xfs_perag*,struct xfs_iunlink*) ; 

__attribute__((used)) static int
xfs_iunlink_change_backref(
	struct xfs_perag	*pag,
	xfs_agino_t		agino,
	xfs_agino_t		next_unlinked)
{
	struct xfs_iunlink	*iu;
	int			error;

	/* Look up the old entry; if there wasn't one then exit. */
	iu = rhashtable_lookup_fast(&pag->pagi_unlinked_hash, &agino,
			xfs_iunlink_hash_params);
	if (!iu)
		return 0;

	/*
	 * Remove the entry.  This shouldn't ever return an error, but if we
	 * couldn't remove the old entry we don't want to add it again to the
	 * hash table, and if the entry disappeared on us then someone's
	 * violated the locking rules and we need to fail loudly.  Either way
	 * we cannot remove the inode because internal state is or would have
	 * been corrupt.
	 */
	error = rhashtable_remove_fast(&pag->pagi_unlinked_hash,
			&iu->iu_rhash_head, xfs_iunlink_hash_params);
	if (error)
		return error;

	/* If there is no new next entry just free our item and return. */
	if (next_unlinked == NULLAGINO) {
		kmem_free(iu);
		return 0;
	}

	/* Update the entry and re-add it to the hash table. */
	iu->iu_next_unlinked = next_unlinked;
	return xfs_iunlink_insert_backref(pag, iu);
}