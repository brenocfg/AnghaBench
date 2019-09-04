#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct isci_host {TYPE_2__* scu_registers; } ;
struct TYPE_3__ {int /*<<< orphan*/  unsolicited_frame_put_pointer; int /*<<< orphan*/  unsolicited_frame_get_pointer; int /*<<< orphan*/  unsolicited_frame_queue_control; } ;
struct TYPE_4__ {TYPE_1__ sdma; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENABLE_BIT ; 
 int /*<<< orphan*/  POINTER ; 
 int /*<<< orphan*/  QUEUE_SIZE ; 
 int /*<<< orphan*/  SCU_MAX_UNSOLICITED_FRAMES ; 
 int SCU_UFQC_GEN_VAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SCU_UFQGP_GEN_BIT (int /*<<< orphan*/ ) ; 
 int SCU_UFQGP_GEN_VAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SCU_UFQPP_GEN_VAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sci_controller_initialize_unsolicited_frame_queue(struct isci_host *ihost)
{
	u32 frame_queue_control_value;
	u32 frame_queue_get_value;
	u32 frame_queue_put_value;

	/* Write the queue size */
	frame_queue_control_value =
		SCU_UFQC_GEN_VAL(QUEUE_SIZE, SCU_MAX_UNSOLICITED_FRAMES);

	writel(frame_queue_control_value,
	       &ihost->scu_registers->sdma.unsolicited_frame_queue_control);

	/* Setup the get pointer for the unsolicited frame queue */
	frame_queue_get_value = (
		SCU_UFQGP_GEN_VAL(POINTER, 0)
		|  SCU_UFQGP_GEN_BIT(ENABLE_BIT)
		);

	writel(frame_queue_get_value,
	       &ihost->scu_registers->sdma.unsolicited_frame_get_pointer);
	/* Setup the put pointer for the unsolicited frame queue */
	frame_queue_put_value = SCU_UFQPP_GEN_VAL(POINTER, 0);
	writel(frame_queue_put_value,
	       &ihost->scu_registers->sdma.unsolicited_frame_put_pointer);
}