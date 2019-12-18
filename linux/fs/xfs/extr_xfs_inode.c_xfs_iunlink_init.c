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

/* Variables and functions */
 int rhashtable_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_iunlink_hash_params ; 

int
xfs_iunlink_init(
	struct xfs_perag	*pag)
{
	return rhashtable_init(&pag->pagi_unlinked_hash,
			&xfs_iunlink_hash_params);
}