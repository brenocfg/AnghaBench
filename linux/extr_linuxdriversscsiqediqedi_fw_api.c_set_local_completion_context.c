#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {TYPE_1__ state; } ;
struct e4_iscsi_task_context {TYPE_3__ ustorm_st_context; TYPE_2__ ystorm_st_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  USTORM_ISCSI_TASK_ST_CTX_LOCAL_COMP ; 
 int /*<<< orphan*/  YSTORM_ISCSI_TASK_STATE_LOCAL_COMP ; 

__attribute__((used)) static void set_local_completion_context(struct e4_iscsi_task_context *context)
{
	SET_FIELD(context->ystorm_st_context.state.flags,
		  YSTORM_ISCSI_TASK_STATE_LOCAL_COMP, 1);
	SET_FIELD(context->ustorm_st_context.flags,
		  USTORM_ISCSI_TASK_ST_CTX_LOCAL_COMP, 1);
}