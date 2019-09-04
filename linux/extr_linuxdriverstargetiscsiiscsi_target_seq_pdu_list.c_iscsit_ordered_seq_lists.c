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
struct iscsi_cmd {size_t seq_count; TYPE_1__* seq_list; } ;
struct TYPE_2__ {scalar_t__ type; scalar_t__ seq_send_order; } ;

/* Variables and functions */
 scalar_t__ SEQTYPE_NORMAL ; 

__attribute__((used)) static void iscsit_ordered_seq_lists(
	struct iscsi_cmd *cmd,
	u8 type)
{
	u32 i, seq_count = 0;

	for (i = 0; i < cmd->seq_count; i++) {
		if (cmd->seq_list[i].type != SEQTYPE_NORMAL)
			continue;
		cmd->seq_list[i].seq_send_order = seq_count++;
	}
}