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
struct kona_pwmc {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ PWM_CONTROL_OFFSET ; 
 int PWM_CONTROL_SMOOTH_SHIFT (unsigned int) ; 
 int PWM_CONTROL_TRIGGER_SHIFT (unsigned int) ; 
 int /*<<< orphan*/  ndelay (int) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void kona_pwmc_prepare_for_settings(struct kona_pwmc *kp,
	unsigned int chan)
{
	unsigned int value = readl(kp->base + PWM_CONTROL_OFFSET);

	value |= 1 << PWM_CONTROL_SMOOTH_SHIFT(chan);
	value &= ~(1 << PWM_CONTROL_TRIGGER_SHIFT(chan));
	writel(value, kp->base + PWM_CONTROL_OFFSET);

	/*
	 * There must be a min 400ns delay between clearing trigger and setting
	 * it. Failing to do this may result in no PWM signal.
	 */
	ndelay(400);
}