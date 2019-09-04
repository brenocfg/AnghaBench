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
typedef  int /*<<< orphan*/  xfs_extlen_t ;
struct xfs_btree_cur {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int
xfs_btree_count_blocks_helper(
	struct xfs_btree_cur	*cur,
	int			level,
	void			*data)
{
	xfs_extlen_t		*blocks = data;
	(*blocks)++;

	return 0;
}