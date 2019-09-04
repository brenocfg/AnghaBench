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
struct urb {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void i_usX2Y_Out04Int(struct urb *urb)
{
#ifdef CONFIG_SND_DEBUG
	if (urb->status) {
		int 		i;
		struct usX2Ydev *usX2Y = urb->context;
		for (i = 0; i < 10 && usX2Y->AS04.urb[i] != urb; i++);
		snd_printdd("i_usX2Y_Out04Int() urb %i status=%i\n", i, urb->status);
	}
#endif
}