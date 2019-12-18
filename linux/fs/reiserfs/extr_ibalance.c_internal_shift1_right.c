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
struct tree_balance {int dummy; } ;
struct buffer_info {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTERNAL_SHIFT_FROM_S_TO_R ; 
 int /*<<< orphan*/  LAST_TO_FIRST ; 
 int /*<<< orphan*/  internal_define_dest_src_infos (int /*<<< orphan*/ ,struct tree_balance*,int,struct buffer_info*,struct buffer_info*,int*,struct buffer_head**) ; 
 int /*<<< orphan*/  internal_insert_key (struct buffer_info*,int /*<<< orphan*/ ,struct buffer_head*,int) ; 
 int /*<<< orphan*/  internal_move_pointers_items (struct buffer_info*,struct buffer_info*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void internal_shift1_right(struct tree_balance *tb,
				  int h, int pointer_amount)
{
	struct buffer_info dest_bi, src_bi;
	struct buffer_head *cf;
	int d_key_position;

	internal_define_dest_src_infos(INTERNAL_SHIFT_FROM_S_TO_R, tb, h,
				       &dest_bi, &src_bi, &d_key_position, &cf);

	/* insert rkey from CFR[h] to right neighbor R[h] */
	if (pointer_amount > 0)
		internal_insert_key(&dest_bi, 0, cf, d_key_position);

	/* last parameter is del_parameter */
	internal_move_pointers_items(&dest_bi, &src_bi, LAST_TO_FIRST,
				     pointer_amount, 1);
}