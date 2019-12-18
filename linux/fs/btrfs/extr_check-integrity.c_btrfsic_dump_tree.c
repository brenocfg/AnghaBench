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
struct btrfsic_state {int /*<<< orphan*/  latest_superblock; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfsic_dump_tree_sub (struct btrfsic_state const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btrfsic_dump_tree(const struct btrfsic_state *state)
{
	btrfsic_dump_tree_sub(state, state->latest_superblock, 0);
}