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
struct mid_pb_ddata {int /*<<< orphan*/  mirqlvl1_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSIC_PWRBTNM ; 
 int intel_scu_ipc_update_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mid_irq_ack(struct mid_pb_ddata *ddata)
{
	return intel_scu_ipc_update_register(ddata->mirqlvl1_addr, 0, MSIC_PWRBTNM);
}