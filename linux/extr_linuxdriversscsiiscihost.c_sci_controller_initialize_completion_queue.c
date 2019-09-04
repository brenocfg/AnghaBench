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
typedef  size_t u32 ;
struct isci_host {int* completion_queue; TYPE_1__* smu_registers; scalar_t__ completion_queue_get; } ;
struct TYPE_2__ {int /*<<< orphan*/  completion_queue_put; int /*<<< orphan*/  completion_queue_get; int /*<<< orphan*/  completion_queue_control; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENABLE ; 
 int /*<<< orphan*/  EVENT_ENABLE ; 
 int /*<<< orphan*/  EVENT_POINTER ; 
 int /*<<< orphan*/  POINTER ; 
 size_t SCU_MAX_COMPLETION_QUEUE_ENTRIES ; 
 scalar_t__ SCU_MAX_EVENTS ; 
 size_t SMU_CQC_EVENT_LIMIT_SET (scalar_t__) ; 
 size_t SMU_CQC_QUEUE_LIMIT_SET (size_t) ; 
 size_t SMU_CQGR_GEN_BIT (int /*<<< orphan*/ ) ; 
 size_t SMU_CQGR_GEN_VAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t SMU_CQPR_GEN_VAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sci_controller_initialize_completion_queue(struct isci_host *ihost)
{
	u32 index;
	u32 completion_queue_control_value;
	u32 completion_queue_get_value;
	u32 completion_queue_put_value;

	ihost->completion_queue_get = 0;

	completion_queue_control_value =
		(SMU_CQC_QUEUE_LIMIT_SET(SCU_MAX_COMPLETION_QUEUE_ENTRIES - 1) |
		 SMU_CQC_EVENT_LIMIT_SET(SCU_MAX_EVENTS - 1));

	writel(completion_queue_control_value,
	       &ihost->smu_registers->completion_queue_control);


	/* Set the completion queue get pointer and enable the queue */
	completion_queue_get_value = (
		(SMU_CQGR_GEN_VAL(POINTER, 0))
		| (SMU_CQGR_GEN_VAL(EVENT_POINTER, 0))
		| (SMU_CQGR_GEN_BIT(ENABLE))
		| (SMU_CQGR_GEN_BIT(EVENT_ENABLE))
		);

	writel(completion_queue_get_value,
	       &ihost->smu_registers->completion_queue_get);

	/* Set the completion queue put pointer */
	completion_queue_put_value = (
		(SMU_CQPR_GEN_VAL(POINTER, 0))
		| (SMU_CQPR_GEN_VAL(EVENT_POINTER, 0))
		);

	writel(completion_queue_put_value,
	       &ihost->smu_registers->completion_queue_put);

	/* Initialize the cycle bit of the completion queue entries */
	for (index = 0; index < SCU_MAX_COMPLETION_QUEUE_ENTRIES; index++) {
		/*
		 * If get.cycle_bit != completion_queue.cycle_bit
		 * its not a valid completion queue entry
		 * so at system start all entries are invalid */
		ihost->completion_queue[index] = 0x80000000;
	}
}