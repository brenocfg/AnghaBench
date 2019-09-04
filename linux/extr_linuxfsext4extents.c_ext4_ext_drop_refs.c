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
struct ext4_ext_path {int p_depth; int /*<<< orphan*/ * p_bh; } ;

/* Variables and functions */
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ *) ; 

void ext4_ext_drop_refs(struct ext4_ext_path *path)
{
	int depth, i;

	if (!path)
		return;
	depth = path->p_depth;
	for (i = 0; i <= depth; i++, path++)
		if (path->p_bh) {
			brelse(path->p_bh);
			path->p_bh = NULL;
		}
}