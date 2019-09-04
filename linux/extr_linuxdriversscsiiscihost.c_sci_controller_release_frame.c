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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int /*<<< orphan*/  get; } ;
struct isci_host {TYPE_2__* scu_registers; TYPE_3__ uf_control; } ;
struct TYPE_4__ {int /*<<< orphan*/  unsolicited_frame_get_pointer; } ;
struct TYPE_5__ {TYPE_1__ sdma; } ;

/* Variables and functions */
 scalar_t__ sci_unsolicited_frame_control_release_frame (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void sci_controller_release_frame(struct isci_host *ihost, u32 frame_index)
{
	if (sci_unsolicited_frame_control_release_frame(&ihost->uf_control, frame_index))
		writel(ihost->uf_control.get,
			&ihost->scu_registers->sdma.unsolicited_frame_get_pointer);
}