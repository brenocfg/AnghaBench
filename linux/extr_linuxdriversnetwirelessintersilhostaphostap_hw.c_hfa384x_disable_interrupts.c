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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFA384X_EVACK_OFF ; 
 int /*<<< orphan*/  HFA384X_INTEN_OFF ; 
 int /*<<< orphan*/  HFA384X_OUTW (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hfa384x_disable_interrupts(struct net_device *dev)
{
	/* disable interrupts and clear event status */
	HFA384X_OUTW(0, HFA384X_INTEN_OFF);
	HFA384X_OUTW(0xffff, HFA384X_EVACK_OFF);
}