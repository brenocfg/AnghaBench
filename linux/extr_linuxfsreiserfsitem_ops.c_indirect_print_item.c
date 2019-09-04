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
typedef  int /*<<< orphan*/  __u32 ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 int I_UNFM_NUM (struct item_head*) ; 
 int UNFM_P_SIZE ; 
 int /*<<< orphan*/  get_block_num (int /*<<< orphan*/ *,int) ; 
 int ih_item_len (struct item_head*) ; 
 int /*<<< orphan*/  print_sequence (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  reiserfs_warning (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ sequence_finished (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_new_sequence (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void indirect_print_item(struct item_head *ih, char *item)
{
	int j;
	__le32 *unp;
	__u32 prev = INT_MAX;
	int num = 0;

	unp = (__le32 *) item;

	if (ih_item_len(ih) % UNFM_P_SIZE)
		reiserfs_warning(NULL, "reiserfs-16102", "invalid item len");

	printk("%d pointers\n[ ", (int)I_UNFM_NUM(ih));
	for (j = 0; j < I_UNFM_NUM(ih); j++) {
		if (sequence_finished(prev, &num, get_block_num(unp, j))) {
			print_sequence(prev, num);
			start_new_sequence(&prev, &num, get_block_num(unp, j));
		}
	}
	print_sequence(prev, num);
	printk("]\n");
}