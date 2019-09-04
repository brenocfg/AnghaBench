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
typedef  int u32 ;
struct iproc_pwmc {scalar_t__ base; } ;

/* Variables and functions */
 int IPROC_PWM_CTRL_EN_SHIFT (unsigned int) ; 
 scalar_t__ IPROC_PWM_CTRL_OFFSET ; 
 int /*<<< orphan*/  ndelay (int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void iproc_pwmc_enable(struct iproc_pwmc *ip, unsigned int channel)
{
	u32 value;

	value = readl(ip->base + IPROC_PWM_CTRL_OFFSET);
	value |= 1 << IPROC_PWM_CTRL_EN_SHIFT(channel);
	writel(value, ip->base + IPROC_PWM_CTRL_OFFSET);

	/* must be a 400 ns delay between clearing and setting enable bit */
	ndelay(400);
}