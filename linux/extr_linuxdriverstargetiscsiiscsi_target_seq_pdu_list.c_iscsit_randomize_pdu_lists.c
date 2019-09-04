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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
struct iscsi_cmd {size_t pdu_count; TYPE_1__* pdu_list; } ;
struct TYPE_2__ {size_t seq_no; size_t pdu_send_order; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  iscsit_create_random_array (size_t*,size_t) ; 
 size_t* kcalloc (size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (size_t*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int iscsit_randomize_pdu_lists(
	struct iscsi_cmd *cmd,
	u8 type)
{
	int i = 0;
	u32 *array, pdu_count, seq_count = 0, seq_no = 0, seq_offset = 0;

	for (pdu_count = 0; pdu_count < cmd->pdu_count; pdu_count++) {
redo:
		if (cmd->pdu_list[pdu_count].seq_no == seq_no) {
			seq_count++;
			continue;
		}
		array = kcalloc(seq_count, sizeof(u32), GFP_KERNEL);
		if (!array) {
			pr_err("Unable to allocate memory"
				" for random array.\n");
			return -ENOMEM;
		}
		iscsit_create_random_array(array, seq_count);

		for (i = 0; i < seq_count; i++)
			cmd->pdu_list[seq_offset+i].pdu_send_order = array[i];

		kfree(array);

		seq_offset += seq_count;
		seq_count = 0;
		seq_no++;
		goto redo;
	}

	if (seq_count) {
		array = kcalloc(seq_count, sizeof(u32), GFP_KERNEL);
		if (!array) {
			pr_err("Unable to allocate memory for"
				" random array.\n");
			return -ENOMEM;
		}
		iscsit_create_random_array(array, seq_count);

		for (i = 0; i < seq_count; i++)
			cmd->pdu_list[seq_offset+i].pdu_send_order = array[i];

		kfree(array);
	}

	return 0;
}