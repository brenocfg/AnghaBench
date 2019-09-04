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
struct musb {int /*<<< orphan*/  g; } ;

/* Variables and functions */
 int /*<<< orphan*/  musb_gadget_wakeup (int /*<<< orphan*/ *) ; 

void musb_g_wakeup(struct musb *musb)
{
	musb_gadget_wakeup(&musb->g);
}