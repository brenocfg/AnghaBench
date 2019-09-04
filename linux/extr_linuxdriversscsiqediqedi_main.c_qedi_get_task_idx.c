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
struct qedi_ctx {int /*<<< orphan*/  task_idx_map; int /*<<< orphan*/  dbg_ctx; } ;
typedef  int s16 ;

/* Variables and functions */
 int MAX_ISCSI_TASK_ENTRIES ; 
 int /*<<< orphan*/  QEDI_ERR (int /*<<< orphan*/ *,char*) ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_and_set_bit (int,int /*<<< orphan*/ ) ; 

int qedi_get_task_idx(struct qedi_ctx *qedi)
{
	s16 tmp_idx;

again:
	tmp_idx = find_first_zero_bit(qedi->task_idx_map,
				      MAX_ISCSI_TASK_ENTRIES);

	if (tmp_idx >= MAX_ISCSI_TASK_ENTRIES) {
		QEDI_ERR(&qedi->dbg_ctx, "FW task context pool is full.\n");
		tmp_idx = -1;
		goto err_idx;
	}

	if (test_and_set_bit(tmp_idx, qedi->task_idx_map))
		goto again;

err_idx:
	return tmp_idx;
}