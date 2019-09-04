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
struct idt_ntb_dev {scalar_t__ cfgspc; } ;
typedef  int /*<<< orphan*/  ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  IDT_REG_ALIGN ; 
 unsigned int const IDT_REG_PCI_MAX ; 
 int /*<<< orphan*/  IS_ALIGNED (unsigned int const,int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/  const,scalar_t__) ; 

__attribute__((used)) static void idt_nt_write(struct idt_ntb_dev *ndev,
			 const unsigned int reg, const u32 data)
{
	/*
	 * It's obvious bug to request a register exceeding the maximum possible
	 * value as well as to have it unaligned.
	 */
	if (WARN_ON(reg > IDT_REG_PCI_MAX || !IS_ALIGNED(reg, IDT_REG_ALIGN)))
		return;

	/* Just write the value to the specified register */
	iowrite32(data, ndev->cfgspc + (ptrdiff_t)reg);
}