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
struct iss_device {scalar_t__* regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISS_HL_IRQENABLE_CLR (int) ; 
 size_t OMAP4_ISS_MEM_ISP_SYS1 ; 
 int /*<<< orphan*/  OMAP4_ISS_MEM_TOP ; 
 int /*<<< orphan*/  iss_reg_write (struct iss_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap4iss_isp_disable_interrupts (struct iss_device*) ; 

__attribute__((used)) static void iss_disable_interrupts(struct iss_device *iss)
{
	if (iss->regs[OMAP4_ISS_MEM_ISP_SYS1])
		omap4iss_isp_disable_interrupts(iss);

	iss_reg_write(iss, OMAP4_ISS_MEM_TOP, ISS_HL_IRQENABLE_CLR(5), ~0);
}