#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tree_balance {int* insert_size; int /*<<< orphan*/  tb_path; } ;
struct item_head {int dummy; } ;
struct TYPE_2__ {int b_size; } ;

/* Variables and functions */
 char M_DELETE ; 
 TYPE_1__* PATH_PLAST_BUFFER (int /*<<< orphan*/ ) ; 
 int UNFM_P_SIZE ; 
 int ih_item_len (struct item_head*) ; 
 scalar_t__ is_direntry_le_ih (struct item_head*) ; 
 scalar_t__ is_indirect_le_ih (struct item_head*) ; 
 scalar_t__ is_statdata_le_ih (struct item_head*) ; 
 struct item_head* tp_item_head (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int calc_deleted_bytes_number(struct tree_balance *tb, char mode)
{
	int del_size;
	struct item_head *p_le_ih = tp_item_head(tb->tb_path);

	if (is_statdata_le_ih(p_le_ih))
		return 0;

	del_size =
	    (mode ==
	     M_DELETE) ? ih_item_len(p_le_ih) : -tb->insert_size[0];
	if (is_direntry_le_ih(p_le_ih)) {
		/*
		 * return EMPTY_DIR_SIZE; We delete emty directories only.
		 * we can't use EMPTY_DIR_SIZE, as old format dirs have a
		 * different empty size.  ick. FIXME, is this right?
		 */
		return del_size;
	}

	if (is_indirect_le_ih(p_le_ih))
		del_size = (del_size / UNFM_P_SIZE) *
				(PATH_PLAST_BUFFER(tb->tb_path)->b_size);
	return del_size;
}