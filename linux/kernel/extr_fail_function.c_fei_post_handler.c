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
struct pt_regs {int dummy; } ;
struct kprobe {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void fei_post_handler(struct kprobe *kp, struct pt_regs *regs,
			     unsigned long flags)
{
	/*
	 * A dummy post handler is required to prohibit optimizing, because
	 * jump optimization does not support execution path overriding.
	 */
}