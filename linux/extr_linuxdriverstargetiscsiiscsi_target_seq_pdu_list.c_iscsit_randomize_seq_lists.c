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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct iscsi_cmd {int seq_count; TYPE_1__* seq_list; } ;
struct TYPE_2__ {scalar_t__ type; int seq_send_order; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ PDULIST_IMMEDIATE ; 
 scalar_t__ PDULIST_IMMEDIATE_AND_UNSOLICITED ; 
 scalar_t__ PDULIST_UNSOLICITED ; 
 scalar_t__ SEQTYPE_NORMAL ; 
 int /*<<< orphan*/  iscsit_create_random_array (int*,int) ; 
 int* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int iscsit_randomize_seq_lists(
	struct iscsi_cmd *cmd,
	u8 type)
{
	int i, j = 0;
	u32 *array, seq_count = cmd->seq_count;

	if ((type == PDULIST_IMMEDIATE) || (type == PDULIST_UNSOLICITED))
		seq_count--;
	else if (type == PDULIST_IMMEDIATE_AND_UNSOLICITED)
		seq_count -= 2;

	if (!seq_count)
		return 0;

	array = kcalloc(seq_count, sizeof(u32), GFP_KERNEL);
	if (!array) {
		pr_err("Unable to allocate memory for random array.\n");
		return -ENOMEM;
	}
	iscsit_create_random_array(array, seq_count);

	for (i = 0; i < cmd->seq_count; i++) {
		if (cmd->seq_list[i].type != SEQTYPE_NORMAL)
			continue;
		cmd->seq_list[i].seq_send_order = array[j++];
	}

	kfree(array);
	return 0;
}