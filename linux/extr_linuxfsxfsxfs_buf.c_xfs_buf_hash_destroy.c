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
struct xfs_perag {int /*<<< orphan*/  pag_buf_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  rhashtable_destroy (int /*<<< orphan*/ *) ; 

void
xfs_buf_hash_destroy(
	struct xfs_perag	*pag)
{
	rhashtable_destroy(&pag->pag_buf_hash);
}