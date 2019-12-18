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
struct tree_balance {int /*<<< orphan*/  tb_path; } ;
struct buffer_info {int /*<<< orphan*/  bi_position; int /*<<< orphan*/  bi_parent; int /*<<< orphan*/  bi_bh; struct tree_balance* tb; } ;

/* Variables and functions */
 int /*<<< orphan*/  PATH_H_POSITION (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PATH_H_PPARENT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PATH_PLAST_BUFFER (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void buffer_info_init_tbS0(struct tree_balance *tb,
                                         struct buffer_info *bi)
{
	bi->tb          = tb;
	bi->bi_bh        = PATH_PLAST_BUFFER(tb->tb_path);
	bi->bi_parent   = PATH_H_PPARENT(tb->tb_path, 0);
	bi->bi_position = PATH_H_POSITION(tb->tb_path, 1);
}