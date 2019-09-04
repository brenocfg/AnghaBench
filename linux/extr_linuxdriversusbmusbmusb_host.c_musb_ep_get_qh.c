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
struct musb_qh {int dummy; } ;
struct musb_hw_ep {struct musb_qh* out_qh; struct musb_qh* in_qh; } ;

/* Variables and functions */

__attribute__((used)) static struct musb_qh *musb_ep_get_qh(struct musb_hw_ep *ep, int is_in)
{
	return is_in ? ep->in_qh : ep->out_qh;
}