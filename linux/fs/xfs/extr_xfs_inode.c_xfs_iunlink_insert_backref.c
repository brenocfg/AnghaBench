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
struct xfs_perag {int /*<<< orphan*/  pagi_unlinked_hash; } ;
struct xfs_iunlink {int /*<<< orphan*/  iu_rhash_head; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int /*<<< orphan*/  kmem_free (struct xfs_iunlink*) ; 
 int rhashtable_insert_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_iunlink_hash_params ; 

__attribute__((used)) static int
xfs_iunlink_insert_backref(
	struct xfs_perag	*pag,
	struct xfs_iunlink	*iu)
{
	int			error;

	error = rhashtable_insert_fast(&pag->pagi_unlinked_hash,
			&iu->iu_rhash_head, xfs_iunlink_hash_params);
	/*
	 * Fail loudly if there already was an entry because that's a sign of
	 * corruption of in-memory data.  Also fail loudly if we see an error
	 * code we didn't anticipate from the rhashtable code.  Currently we
	 * only anticipate ENOMEM.
	 */
	if (error) {
		WARN(error != -ENOMEM, "iunlink cache insert error %d", error);
		kmem_free(iu);
	}
	/*
	 * Absorb any runtime errors that aren't a result of corruption because
	 * this is a cache and we can always fall back to bucket list scanning.
	 */
	if (error != 0 && error != -EEXIST)
		error = 0;
	return error;
}