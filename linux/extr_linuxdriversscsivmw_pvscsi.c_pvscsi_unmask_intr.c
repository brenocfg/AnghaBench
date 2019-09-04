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
typedef  int /*<<< orphan*/  u32 ;
struct pvscsi_adapter {scalar_t__ use_msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVSCSI_INTR_CMPL_MASK ; 
 int /*<<< orphan*/  PVSCSI_INTR_MSG_MASK ; 
 int /*<<< orphan*/  PVSCSI_REG_OFFSET_INTR_MASK ; 
 int /*<<< orphan*/  pvscsi_reg_write (struct pvscsi_adapter const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pvscsi_unmask_intr(const struct pvscsi_adapter *adapter)
{
	u32 intr_bits;

	intr_bits = PVSCSI_INTR_CMPL_MASK;
	if (adapter->use_msg)
		intr_bits |= PVSCSI_INTR_MSG_MASK;

	pvscsi_reg_write(adapter, PVSCSI_REG_OFFSET_INTR_MASK, intr_bits);
}