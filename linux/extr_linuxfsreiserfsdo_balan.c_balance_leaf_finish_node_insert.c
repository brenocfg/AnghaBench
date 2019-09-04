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
struct tree_balance {int /*<<< orphan*/ * lkey; scalar_t__* CFL; int /*<<< orphan*/  item_pos; int /*<<< orphan*/  zeroes_num; int /*<<< orphan*/  tb_path; } ;
struct item_head {int dummy; } ;
struct buffer_info {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 struct buffer_head* PATH_PLAST_BUFFER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_info_init_tbS0 (struct tree_balance*,struct buffer_info*) ; 
 int /*<<< orphan*/  leaf_insert_into_buf (struct buffer_info*,int /*<<< orphan*/ ,struct item_head* const,char const* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  replace_key (struct tree_balance*,scalar_t__,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void balance_leaf_finish_node_insert(struct tree_balance *tb,
					    struct item_head * const ih,
					    const char * const body)
{
	struct buffer_head *tbS0 = PATH_PLAST_BUFFER(tb->tb_path);
	struct buffer_info bi;
	buffer_info_init_tbS0(tb, &bi);
	leaf_insert_into_buf(&bi, tb->item_pos, ih, body, tb->zeroes_num);

	/* If we insert the first key change the delimiting key */
	if (tb->item_pos == 0) {
		if (tb->CFL[0])	/* can be 0 in reiserfsck */
			replace_key(tb, tb->CFL[0], tb->lkey[0], tbS0, 0);

	}
}