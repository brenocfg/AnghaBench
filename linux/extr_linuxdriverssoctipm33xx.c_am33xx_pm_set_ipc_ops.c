#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_8__ {scalar_t__* resume_offset; } ;
struct TYPE_7__ {TYPE_1__* ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* set_resume_address ) (TYPE_2__*,void*) ;int /*<<< orphan*/  (* set_mem_type ) (TYPE_2__*,int) ;} ;

/* Variables and functions */
 scalar_t__ am33xx_do_wfi_sram_phys ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* m3_ipc ; 
 int /*<<< orphan*/  pm33xx_dev ; 
 TYPE_4__* pm_sram ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,void*) ; 
 int ti_emif_get_mem_type () ; 

__attribute__((used)) static void am33xx_pm_set_ipc_ops(void)
{
	u32 resume_address;
	int temp;

	temp = ti_emif_get_mem_type();
	if (temp < 0) {
		dev_err(pm33xx_dev, "PM: Cannot determine memory type, no PM available\n");
		return;
	}
	m3_ipc->ops->set_mem_type(m3_ipc, temp);

	/* Physical resume address to be used by ROM code */
	resume_address = am33xx_do_wfi_sram_phys +
			 *pm_sram->resume_offset + 0x4;

	m3_ipc->ops->set_resume_address(m3_ipc, (void *)resume_address);
}