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
struct tree_balance {int /*<<< orphan*/ * FL; int /*<<< orphan*/ * L; } ;
struct buffer_info {int /*<<< orphan*/  bi_position; int /*<<< orphan*/  bi_parent; int /*<<< orphan*/  bi_bh; struct tree_balance* tb; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_left_neighbor_position (struct tree_balance*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void buffer_info_init_left(struct tree_balance *tb,
                                         struct buffer_info *bi)
{
	bi->tb          = tb;
	bi->bi_bh       = tb->L[0];
	bi->bi_parent   = tb->FL[0];
	bi->bi_position = get_left_neighbor_position(tb, 0);
}