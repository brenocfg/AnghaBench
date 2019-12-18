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
struct item_head {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int B_NR_ITEMS (struct buffer_head*) ; 
 int /*<<< orphan*/  check_leaf_block_head (struct buffer_head*) ; 
 int /*<<< orphan*/  ih_item_body (struct buffer_head*,struct item_head*) ; 
 struct item_head* item_head (struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  op_check_item (struct item_head*,int /*<<< orphan*/ ) ; 

void check_leaf(struct buffer_head *bh)
{
	int i;
	struct item_head *ih;

	if (!bh)
		return;
	check_leaf_block_head(bh);
	for (i = 0, ih = item_head(bh, 0); i < B_NR_ITEMS(bh); i++, ih++)
		op_check_item(ih, ih_item_body(bh, ih));
}