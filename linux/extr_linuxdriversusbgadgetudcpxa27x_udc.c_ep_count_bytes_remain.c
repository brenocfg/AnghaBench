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
struct pxa_ep {scalar_t__ dir_in; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  UDCBCR ; 
 int udc_ep_readl (struct pxa_ep*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ep_count_bytes_remain(struct pxa_ep *ep)
{
	if (ep->dir_in)
		return -EOPNOTSUPP;
	return udc_ep_readl(ep, UDCBCR) & 0x3ff;
}