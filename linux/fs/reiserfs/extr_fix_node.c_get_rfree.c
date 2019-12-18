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
struct tree_balance {int /*<<< orphan*/  tb_path; struct buffer_head** FR; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_N_CHILD (struct buffer_head*,int) ; 
 int MAX_CHILD_SIZE (struct buffer_head*) ; 
 int PATH_H_B_ITEM_ORDER (int /*<<< orphan*/ ,int) ; 
 struct buffer_head* PATH_H_PPARENT (int /*<<< orphan*/ ,int) ; 
 int dc_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_rfree(struct tree_balance *tb, int h)
{
	struct buffer_head *r, *f;
	int order;

	if ((f = PATH_H_PPARENT(tb->tb_path, h)) == NULL ||
	    (r = tb->FR[h]) == NULL)
		return 0;

	if (f == r)
		order = PATH_H_B_ITEM_ORDER(tb->tb_path, h) + 1;
	else {
		order = 0;
		f = r;
	}

	return (MAX_CHILD_SIZE(f) - dc_size(B_N_CHILD(f, order)));

}