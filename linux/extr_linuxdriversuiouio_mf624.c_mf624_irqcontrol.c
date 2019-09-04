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
struct uio_info {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ALL ; 
 int /*<<< orphan*/  mf624_disable_interrupt (int /*<<< orphan*/ ,struct uio_info*) ; 
 int /*<<< orphan*/  mf624_enable_interrupt (int /*<<< orphan*/ ,struct uio_info*) ; 

__attribute__((used)) static int mf624_irqcontrol(struct uio_info *info, s32 irq_on)
{
	if (irq_on == 0)
		mf624_disable_interrupt(ALL, info);
	else if (irq_on == 1)
		mf624_enable_interrupt(ALL, info);

	return 0;
}