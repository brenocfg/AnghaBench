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

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RADIX_TREE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THRASH_SIZE ; 
 int /*<<< orphan*/  do_thrash (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  item_kill_tree (int /*<<< orphan*/ *) ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree ; 
 int /*<<< orphan*/  verify_tag_consistency (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void thrash_tags(void)
{
	RADIX_TREE(tree, GFP_KERNEL);
	char *thrash_state;

	thrash_state = malloc(THRASH_SIZE);
	memset(thrash_state, 0, THRASH_SIZE);

	do_thrash(&tree, thrash_state, 0);

	verify_tag_consistency(&tree, 0);
	item_kill_tree(&tree);
	free(thrash_state);
}