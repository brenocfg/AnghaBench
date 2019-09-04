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
struct xfs_perag {int /*<<< orphan*/  pag_buf_hash; int /*<<< orphan*/  pag_buf_lock; } ;

/* Variables and functions */
 int rhashtable_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_buf_hash_params ; 

int
xfs_buf_hash_init(
	struct xfs_perag	*pag)
{
	spin_lock_init(&pag->pag_buf_lock);
	return rhashtable_init(&pag->pag_buf_hash, &xfs_buf_hash_params);
}